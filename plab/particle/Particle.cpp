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

#ifndef PLAB_SKIP_GLEW_INCLUDE

#include <GL/glew.h>

#endif


#include <GL/gl.h>

#include "Particle.h"

void Particle::enableVAOAttributes( )
{
  glEnableVertexAttribArray( 1 );
  glVertexAttribPointer( 1 , 3 , GL_FLOAT , GL_FALSE , sizeof( Particle ) ,
                         ( void* ) 0 );
  glVertexAttribDivisor( 1 , 1 );

  glEnableVertexAttribArray( 2 );
  glVertexAttribPointer( 2 , 4 , GL_FLOAT , GL_FALSE , sizeof( Particle ) ,
                         ( void* ) ( sizeof( float ) * 3 ));
  glVertexAttribDivisor( 2 , 1 );

  glEnableVertexAttribArray( 3 );
  glVertexAttribPointer( 3 , 1 , GL_FLOAT , GL_FALSE , sizeof( Particle ) ,
                         ( void* ) ( sizeof( float ) * 7 ));
  glVertexAttribDivisor( 3 , 1 );

  glEnableVertexAttribArray( 4 );
  glVertexAttribPointer( 4 , 1 , GL_FLOAT , GL_FALSE , sizeof( Particle ) ,
                         ( void* ) ( sizeof( float ) * 8 ));
  glVertexAttribDivisor( 4 , 1 );
}
