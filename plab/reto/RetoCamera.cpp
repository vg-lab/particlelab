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

#include "RetoCamera.h"

#include <glm/glm.hpp>

namespace plab
{

  glm::mat4x4 RetoCamera::iCameraViewProjectionMatrix( ) const
  {
    return floatPtrToMat4( _camera->projectionViewMatrix( ));
  }

  glm::mat4x4 RetoCamera::iCameraViewMatrix( ) const
  {
    return floatPtrToMat4( _camera->viewMatrix( ));
  }

  glm::vec3 RetoCamera::iCameraPosition( ) const
  {
    return floatPtrToVec3( position( ).data( ));
  }

  glm::vec3 RetoCamera::floatPtrToVec3( float* floatPos )
  {
    return { floatPos[ 0 ] ,
             floatPos[ 1 ] ,
             floatPos[ 2 ] };
  }

  glm::mat4x4 RetoCamera::floatPtrToMat4( float* floatPos )
  {
    return { floatPos[ 0 ] , floatPos[ 1 ] ,
             floatPos[ 2 ] , floatPos[ 3 ] ,
             floatPos[ 4 ] , floatPos[ 5 ] ,
             floatPos[ 6 ] , floatPos[ 7 ] ,
             floatPos[ 8 ] , floatPos[ 9 ] ,
             floatPos[ 10 ] , floatPos[ 11 ] ,
             floatPos[ 12 ] , floatPos[ 13 ] ,
             floatPos[ 14 ] , floatPos[ 15 ] };
  }
}