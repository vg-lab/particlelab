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

#include "CoverageRenderer.h"

#include <plab/core/AbstractCluster.h>
#include <plab/core/Model.h>

namespace plab
{
  CoverageRenderer::CoverageRenderer( uint32_t program )
    : Renderer( program )
    , cache( program )
  {

  }

  void CoverageRenderer::render( const AbstractCluster& cluster )
  {
    glUseProgram( _program );

    auto& model = cluster.getModel( );
    bool accumulative = false;
    if ( model != nullptr )
    {
      model->uploadDrawUniforms( cache );
      accumulative = model->isAccumulativeMode( );
    }

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );

    if ( accumulative )
    {
      glDepthMask( GL_FALSE );
      glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_CONSTANT_ALPHA );
    }
    else
    {
      glDepthMask( GL_TRUE );
      glEnable( GL_SAMPLE_ALPHA_TO_COVERAGE );
      glEnable( GL_SAMPLE_ALPHA_TO_ONE );
      glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
    }

    cluster.bindVAO( );

    auto size = static_cast<GLsizei>(cluster.size( ));
    glDrawArraysInstanced( GL_TRIANGLE_STRIP , 0 , 4 , size );

    if ( !accumulative )
    {
      glDisable( GL_SAMPLE_ALPHA_TO_COVERAGE );
      glDisable( GL_SAMPLE_ALPHA_TO_ONE );
    }

    glBindVertexArray( 0 );

    glDepthMask( GL_TRUE );
    glEnable( GL_CULL_FACE );
  }
}