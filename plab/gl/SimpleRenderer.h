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

#ifndef PLAB_SimpleRenderer_H
#define PLAB_SimpleRenderer_H


#include <plab/api.h>
#include <plab/core/Renderer.h>
#include <plab/core/UniformCache.h>

namespace plab
{

  /**
   * A particle renderer that just renders them,
   * leaving all the configuration to the external
   * application.
   */
  class PLAB_API SimpleRenderer : public Renderer
  {

    UniformCache cache;

  public:

    /**
     * Creates the simple renderer.
     * @param program the shader program to use.
     */
    explicit SimpleRenderer( uint32_t program );

    ~SimpleRenderer( ) override = default;

    void render( const AbstractCluster& cluster ) override;

  };
}

#endif //PLAB_SimpleRenderer_H
