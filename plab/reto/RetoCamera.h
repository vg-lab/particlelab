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

#ifndef PLAB_RETOCAMERA_H
#define PLAB_RETOCAMERA_H

#include <plab/api.h>
#include <plab/core/ICamera.h>

#include <reto/reto.h>

namespace plab
{

  /**
   * This class merges the reto's OrbitalCameraController
   * with this API ICamera.
   */
  class PLAB_API RetoCamera
    : public ICamera , public reto::OrbitalCameraController
  {

    static glm::vec3 floatPtrToVec3( float* floatPos );

    static glm::mat4x4 floatPtrToMat4( float* floatPos );

  public:

    glm::vec3 iCameraPosition( ) const override;

    glm::mat4x4 iCameraViewMatrix( ) const override;

    glm::mat4x4 iCameraViewProjectionMatrix( ) const override;

  };
}


#endif //PLAB_RETOCAMERA_H
