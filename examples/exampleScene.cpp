//
// Created by gaelr on 07/06/2022.
//


#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include <iostream>
#include "plab/core/Cluster.h"
#include "plab/core/Updater.h"
#include "plab/reto/RetoCamera.h"
#include "plab/gl/CoverageRenderer.h"
#include "plab/reto/CameraModel.h"

const static std::string plabVertexShader = R"(#version 330
#extension GL_ARB_separate_shader_objects: enable

uniform mat4 viewProjectionMatrix;
uniform vec3 cameraUp;
uniform vec3 cameraRight;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 particlePosition;
layout(location = 2) in vec4 particleColor;
layout(location = 3) in float particleLife;
layout(location = 4) in float particleSize;

out vec4 color;
out vec2 uvCoord;
out float size;

void main()
{
    float pSize = max(particleSize, 0);
    gl_Position = viewProjectionMatrix
    * vec4(
    (vertexPosition.x * pSize * cameraRight)
    + (vertexPosition.y * pSize * cameraUp)
    + particlePosition, 1.0) - vec4(0.0, 0.0, 0.1, 0.0);
    color = particleColor;
    uvCoord = vertexPosition.rg + vec2(0.5, 0.5);
    size = pSize;
})";

const static std::string plabFragmentShader = R"(#version 330
in vec4 color;
in vec2 uvCoord;
in float size;

out vec4 outputColor;

uniform float threshold;

void main()
{
  vec2 p = -1.0 + 2.0 * uvCoord;
  float l = sqrt( dot( p,p ));
  l = 1.0 - clamp( l, 0.0, 1.0 );

  float margin = 1.0 - threshold;
  float alpha =
    float(l <= margin) + (float(l > margin) * (1.0 -((l - margin) / (1.0 - margin))));
  alpha = 1.0 - alpha;

  //outputColor = vec4( vec3( linealDepth ), 1.0 );
  //outputColor = vec4( vec3( fragmentDepth ), 1.0 );

  outputColor = vec4( color.rgb, alpha * color.a );
})";

const static std::string computeShader = R"(#version 430 core

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

struct particle_data {
    float px, py, pz;
    float red, green, blue, alpha;
    float life;
    float size;
};

layout (std430, binding = 0) buffer ParticleBuffer {
    particle_data particles[];
};

uniform float deltaSeconds;

void main(void)
{
    uint index = gl_GlobalInvocationID.x;
    particle_data particle = particles[index];
    particle.py = particle.py - 10.0 * deltaSeconds * (((index + 7) * 2) % 10 / 10.0f + 0.05f);
    //particle.py = particle.py - 10.0 * deltaSeconds;
    particle.size = (index % 10) / 10.0f;
    particles[index] = particle;
})";

std::shared_ptr< plab::RetoCamera > camera;
std::shared_ptr< plab::Cluster < Particle>>
cluster;
std::chrono::high_resolution_clock::time_point lastTick;
float deltaSeconds = 0.0f;

class DeltaTimeModel : public plab::CameraModel
{
public:
  DeltaTimeModel( const std::shared_ptr< plab::ICamera >& c )
    : CameraModel( c )
  { }

  void uploadComputeUniforms( plab::UniformCache& cache ) const override
  {
    glUniform1f( cache.getLocation( "deltaSeconds" ) , deltaSeconds );
  }
};


void idle( )
{
  auto now = std::chrono::high_resolution_clock::now( );
  std::chrono::duration< float , std::ratio< 1 , 1>> delay = now - lastTick;
  deltaSeconds = delay.count( );
  lastTick = now;

  camera->rotate( Eigen::Vector3f( 0.1f * deltaSeconds , 0 , 0 ));
  glutPostRedisplay( );
}

void resize( int width , int height )
{
  camera->windowSize( width , height );
  glViewport( 0 , 0 , width , height );
}

void draw( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  camera->anim( );
  cluster->update( );
  cluster->render( );

  glutSwapBuffers( );
}

int main( int argc , char* argv[] )
{
  glutInit( &argc , argv );
  glutInitContextVersion( 3 , 3 );
  glutInitContextFlags( GLUT_FORWARD_COMPATIBLE );
  glutInitContextProfile( GLUT_CORE_PROFILE );

  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize( 500 , 500 );
  glutInitWindowPosition( 0 , 0 );
  glutCreateWindow( "GLUT example" );

  glewExperimental = GL_TRUE;
  GLenum err = glewInit( );
  if ( GLEW_OK != err )
  {
    std::cout << "Error: " << glewGetErrorString( err ) << std::endl;
    exit( -1 );
  }
  const GLubyte* oglVersion = glGetString( GL_VERSION );
  std::cout << "This system supports OpenGL Version: "
            << oglVersion << std::endl;

  camera = std::make_shared< plab::RetoCamera >( );
  camera->camera( )->nearPlane( 0.001f );
  camera->camera( )->farPlane( 100.0f );

  constexpr int AMOUNT = 2000000;
  std::vector< Particle > particles( AMOUNT );

  srand( time( NULL ));

  for ( int i = 0; i < AMOUNT; ++i )
  {
    Particle p = Particle( );
    p.life = 1.0f;
    p.size = 1.0f;
    p.color = glm::vec4(
      rand( ) % 100 / 100.0f ,
      rand( ) % 100 / 100.0f ,
      rand( ) % 100 / 100.0f ,
      1.0 );
    p.position = glm::vec3(
      rand( ) % 200 - 100 ,
      rand( ) % 200 - 100 ,
      rand( ) % 200 - 100
    );
    particles.at( i ) = p;
  }

  auto program = reto::ShaderProgram( );
  program.loadFromText( plabVertexShader , plabFragmentShader );
  program.create( );
  program.link( );

  auto computeProgram = reto::ShaderProgram( );
  computeProgram.loadComputeShaderFromText( computeShader );
  computeProgram.create( );
  computeProgram.link( );

  auto renderer = std::make_shared< plab::CoverageRenderer >(
    program.program( ));
  auto model = std::make_shared< DeltaTimeModel >( camera );
  model->setAccumulativeMode( true );

  auto updater = std::make_shared< plab::Updater >( computeProgram.program( ));

  cluster = std::make_shared< plab::Cluster < Particle>>( );
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  cluster->setRenderer( renderer );
  cluster->setModel( model );
  cluster->setUpdater( updater );
  cluster->setParticles( particles );
  particles.clear( );

  glClearColor( 0.1f , 0.1f , 0.1f , 1.0f );
  lastTick = std::chrono::high_resolution_clock::now( );

  glutReshapeFunc( resize );
  glutIdleFunc( idle );
  glutDisplayFunc( draw );
  glutMainLoop( );
}