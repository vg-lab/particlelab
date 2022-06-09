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

#ifndef PLAB_MODEL_H
#define PLAB_MODEL_H

#include <plab/api.h>

namespace plab
{
  class UniformCache;

  /**
   * Represents a cluster's general data.
   *
   * You can extend this class if you want
   * to upload draw and compute uniforms when the
   * cluster is rendered or updated.
   *
   * Several clusters can share the same model.
   */
  class PLAB_API Model
  {

    bool _accumulativeMode;

  public:

    /**
     * Creates the model.
     */
    Model( )
      : _accumulativeMode( false )
    { };

    /**
     * The destructor of the model.
     */
    virtual ~Model( ) = default;

    /**
     * Returns whether the cluster should use the accumulative mode.
     * @return whether the cluster should use the accumulative mode.
     */
    bool isAccumulativeMode( ) const
    {
      return _accumulativeMode;
    }

    /**
     * Sets whether the cluster should use the accumulative mode.
     * @param accumulativeMode whether the cluster
     * should use the accumulative mode.
     */
    void setAccumulativeMode( bool accumulativeMode )
    {
      _accumulativeMode = accumulativeMode;
    }

    /**
     * Use this method to upload all draw uniforms you want.
     *
     * The shader program is already bind when this method is invoked.
     *
     * You can use the given UniformCache to access the uniform's
     * locations easily.
     *
     * @param cache the cache.
     */
    virtual void uploadDrawUniforms( plab::UniformCache& cache ) const = 0;

    /**
     * Use this method to upload all compute uniforms you want.
     *
     * The shader program is already bind when this method is invoked.
     *
     * You can use the given UniformCache to access the uniform's
     * locations easily.
     *
     * @param cache the cache.
     */
    virtual void uploadComputeUniforms( plab::UniformCache& cache ) const = 0;

  };
}


#endif //PLAB_MODEL_H
