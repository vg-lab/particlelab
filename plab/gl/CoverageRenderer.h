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

#ifndef PLAB_COVERAGERENDERER_H
#define PLAB_COVERAGERENDERER_H


#include <plab/api.h>
#include <plab/core/Renderer.h>
#include <plab/core/UniformCache.h>

namespace plab
{

  /**
   * A particle renderer that uses the coverage technique to
   * render transparent particles.
   *
   * This renderer requires a multisampling setup to work.
   */
  class PLAB_API CoverageRenderer : public Renderer
  {

    UniformCache cache;

  public:

    /**
     * Creates the coverage renderer.
     * @param program the shader program to use.
     */
    explicit CoverageRenderer( GLuint program );

    ~CoverageRenderer( ) override = default;

    void render( const AbstractCluster& cluster ) override;

  };
}

#endif //PLAB_COVERAGERENDERER_H
