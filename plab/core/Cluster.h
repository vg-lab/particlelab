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

#ifndef PLAB_CLUSTER_H
#define PLAB_CLUSTER_H

#include "AbstractCluster.h"

#include <plab/api.h>
#include <plab/particle/Particle.h>

#include <vector>

namespace plab
{

  /**
   * Represents a group of particles with the same parameters
   * that are rendered at the same time with the same Model and
   * Updater.
   *
   * You can define the particle type you want to use in a cluster.
   *
   * @tparam P the type of particle.
   */
  template< class P = Particle >
  class Cluster : public AbstractCluster
  {

  public:

    /**
     * Creates the cluster.
     * This constructor also creates all required OpenGL objects.
     */
    Cluster( )
      : AbstractCluster( )
    {
      P::enableVAOAttributes( );
    }

    uint64_t particleSize( ) const override
    {
      return sizeof( P );
    }

    /**
     * Uploads the given particles.
     * This overrides the already present particles.
     *
     * @param particles the particles.
     */
    void setParticles( std::vector< P > particles )
    {
      setParticlesRaw( particles.data( ) , particles.size( ));
    }

    /**
     * Maps the data buffer into memory, returning a
     * pointer to the underlying data.
     *
     * You can read from and write to this
     * data.
     *
     * You can't expand or shrink the buffer.
     * The buffer will have the same amount of
     * particles you defined before.
     *
     * You can't draw or update this cluster
     * while the data buffer is mapped.
     *
     * @return the pointer to the buffer.
     *
     * @see <a href="https://www.khronos.org/opengl/wiki/Buffer_Object#Mapping">
     * Buffer Object / Mapping</a>
     */
    P* mapData( )
    {
      return ( P* ) mapDataRaw( );
    }
  };
}
#endif //PLAB_CLUSTER_H
