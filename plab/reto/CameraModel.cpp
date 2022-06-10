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
#include <GL/gl.h>

#include "CameraModel.h"

#include <utility>
#include "plab/core/UniformCache.h"
#include "plab/core/ICamera.h"


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace plab
{
  CameraModel::CameraModel( std::shared_ptr< plab::ICamera > camera )
    : Model( )
    , _camera( std::move(( camera )))
  {

  }

  void CameraModel::uploadDrawUniforms( plab::UniformCache& cache ) const
  {
    const glm::mat4x4 tmp = _camera->iCameraViewProjectionMatrix( );
    const glm::mat4x4& viewMatrix = _camera->iCameraViewMatrix( );

    glUniformMatrix4fv(
      cache.getLocation( "viewProjectionMatrix" ) ,
      1 ,
      GL_FALSE ,
      glm::value_ptr( tmp )
    );

    glUniform3f(
      cache.getLocation( "cameraUp" ) ,
      viewMatrix[ 0 ][ 1 ] ,
      viewMatrix[ 1 ][ 1 ] ,
      viewMatrix[ 2 ][ 1 ]
    );

    glUniform3f(
      cache.getLocation( "cameraRight" ) ,
      viewMatrix[ 0 ][ 0 ] ,
      viewMatrix[ 1 ][ 0 ] ,
      viewMatrix[ 2 ][ 0 ]
    );

    glUniform1f(
      cache.getLocation( "threshold" ) ,
      0.45f
    );
  }

  void CameraModel::uploadComputeUniforms( plab::UniformCache& ) const
  {

  }
}
