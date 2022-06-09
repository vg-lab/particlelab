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

#ifndef PLAB_UPDATER_H
#define PLAB_UPDATER_H


#include <plab/api.h>
#include "UniformCache.h"

#include <GL/glew.h>
#include <GL/gl.h>


namespace plab
{

  class AbstractCluster;

  /**
   * Class used by clusters to update its particles using a compute shader.
   *
   * You may extend this class to provide more complex behaviours.
   *
   * Several clusters can share the same updater.
   */
  class PLAB_API Updater
  {

  protected:

    GLuint _program;
    UniformCache _cache;

  public:

    /**
     * Creates the updater.
     * @param program the identifier of the computer shader program.
     */
    explicit Updater( GLuint program );

    /**
     * The destructor of the updater.
     */
    virtual ~Updater( ) = default;

    /**
     * Updates the cluster.
     * @param cluster the cluster to update.
     */
    virtual void update( AbstractCluster& cluster );

  };
}


#endif //PLAB_UPDATER_H
