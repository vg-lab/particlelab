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

#ifndef __PLAB__ICAMERA__
#define __PLAB__ICAMERA__

#include <plab/api.h>

#include <glm/fwd.hpp>

namespace plab
{

  /*! \class ICamera
   *
   * This class provides an interface to integrate external camera
   * implementations by simply implementing its methods.
   *
   */
  class PLAB_API ICamera
  {
  public:

    /*! \brief Default constructor.
     *
     * Default constructor.
     *
     */
    ICamera( ) = default;

    /*! \brief Default destructor.
     *
     * Default destructor.
     *
     */
    virtual ~ICamera( ) = default;

    /*! \brief This method returns the current camera position.
     *
     * This method returns the current camera position. Implement to be used
     * within the particle system.
     *
     * @return Current camera position.
     */
    virtual glm::vec3 iCameraPosition( ) const = 0;

    /*! \brief This method returns the current view matrix.
     *
     * This method returns the current view matrix. Implement to be used
     * within the particle system.
     *
     * @return Current view matrix.
     */
    virtual glm::mat4x4 iCameraViewMatrix( ) const = 0;

    /*! \brief This method returns the current view projection matrix.
     *
     * This method returns the current view projection matrix.
     *
     * @return Current view projection matrix.
     */
    virtual glm::mat4x4 iCameraViewProjectionMatrix( ) const = 0;
  };
}

#endif /* __PLAB__ICAMERA__ */
