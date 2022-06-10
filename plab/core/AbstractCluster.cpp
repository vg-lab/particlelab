// Copyright (c) 2022-2022 VG-Lab/URJC.
//
// Authors:
// - Gael Rial Costas <g.rial.2018@alumnos.urjc.es>
//
// This file is part of ParticleLab
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 3.0 as published
// by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
// details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//

//
// Created by gaeqs on 7/06/22.
//

#include "AbstractCluster.h"

#include "Renderer.h"
#include "Updater.h"
#include <iostream>

namespace plab
{

  AbstractCluster::AbstractCluster( )
    : _renderer( nullptr )
    , _model( nullptr )
    , _updater( nullptr )
    , _vaoBuffer( 0 )
    , _vertexBuffer( 0 )
    , _dataBuffer( 0 )
    , _size( 0 )
  {
    const GLfloat vertices[] = { -0.5f , -0.5f , 0.0f , 0.5f , -0.5f , 0.0f ,
                                 -0.5f , 0.5f , 0.0f , 0.5f , 0.5f , 0.0f };

    glGenVertexArrays( 1 , &_vaoBuffer );
    glBindVertexArray( _vaoBuffer );

    glGenBuffers( 1 , &_vertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER , _vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER , sizeof( vertices ) , &vertices ,
                  GL_STATIC_DRAW );

    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE , 0 , nullptr );

    glGenBuffers( 1 , &_dataBuffer );

    // This is for the computing shader.
    //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _dataBuffer);

    glBindBuffer( GL_ARRAY_BUFFER , _dataBuffer );
  }

  AbstractCluster::~AbstractCluster( )
  {
    glDeleteVertexArrays( 1 , &_vaoBuffer );
    glDeleteBuffers( 1 , &_dataBuffer );
    glDeleteBuffers( 1 , &_vertexBuffer );
  }


  const std::shared_ptr< Renderer >& AbstractCluster::getRenderer( ) const
  {
    return _renderer;
  }

  void
  AbstractCluster::setRenderer( const std::shared_ptr< Renderer >& renderer )
  {
    _renderer = renderer;
  }

  const std::shared_ptr< Model >& AbstractCluster::getModel( ) const
  {
    return _model;
  }

  void AbstractCluster::setModel( const std::shared_ptr< Model >& model )
  {
    _model = model;
  }

  const std::shared_ptr< Updater >& AbstractCluster::getUpdater( ) const
  {
    return _updater;
  }

  void AbstractCluster::setUpdater( const std::shared_ptr< Updater >& updater )
  {
    _updater = updater;
  }

  uint32_t AbstractCluster::size( ) const
  {
    return _size;
  }


  void AbstractCluster::setParticlesRaw( void* data , uint64_t amount )
  {
    auto size = amount * static_cast<uint64_t>(particleSize( ));
    glBindBuffer( GL_ARRAY_BUFFER , _dataBuffer );
    glBufferData( GL_ARRAY_BUFFER , size , data , GL_DYNAMIC_COPY );
    _size = amount;
  }

  void AbstractCluster::allocateBuffer( uint64_t particles )
  {
    auto size = particles * static_cast<uint64_t>(particleSize( ));

    glBufferData( GL_ARRAY_BUFFER , size , nullptr , GL_DYNAMIC_COPY );
    _size = particles;
  }

  void AbstractCluster::bindVAO( ) const
  {
    glBindVertexArray( _vaoBuffer );
  }

  void AbstractCluster::update( ) const
  {
    if ( _updater != nullptr )
    {
      _updater->update( *this );
    }
  }

  void AbstractCluster::render( ) const
  {
    if ( _renderer != nullptr )
    {
      _renderer->render( *this );
    }
  }

  GLuint AbstractCluster::getVaoBuffer( ) const
  {
    return _vaoBuffer;
  }

  GLuint AbstractCluster::getVertexBuffer( ) const
  {
    return _vertexBuffer;
  }

  GLuint AbstractCluster::getDataBuffer( ) const
  {
    return _dataBuffer;
  }

  void* AbstractCluster::mapDataRaw( ) const
  {
    glBindBuffer( GL_ARRAY_BUFFER , _dataBuffer );
    return glMapBuffer( GL_ARRAY_BUFFER , GL_READ_WRITE );
  }

  void AbstractCluster::unmapData( ) const
  {
    glBindBuffer( GL_ARRAY_BUFFER , _dataBuffer );
    glUnmapBuffer( _dataBuffer );
  }
}