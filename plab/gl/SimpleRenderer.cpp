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
// Created by gaeqs on 8/06/22.
//

#ifndef PLAB_SKIP_GLEW_INCLUDE

#include <GL/glew.h>

#endif

#include "SimpleRenderer.h"

#include <plab/core/AbstractCluster.h>
#include <plab/core/Model.h>

namespace plab
{
  SimpleRenderer::SimpleRenderer( uint32_t program )
    : Renderer( program )
    , cache( program )
  {

  }

  void SimpleRenderer::render( const AbstractCluster& cluster )
  {
    glUseProgram( _program );

    auto& model = cluster.getModel( );
    if ( model != nullptr )
    {
      model->uploadDrawUniforms( cache );
    }
    cluster.bindVAO( );
    auto size = static_cast<GLsizei>(cluster.size( ));
    glDrawArraysInstanced( GL_TRIANGLE_STRIP , 0 , 4 , size );
    glBindVertexArray( 0 );
  }
}