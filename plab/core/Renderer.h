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

#ifndef PLAB_RENDERER_H
#define PLAB_RENDERER_H

#include <plab/api.h>

#include <GL/gl.h>


namespace plab
{
  class AbstractCluster;

  /**
   * Children of this class are used to render clusters.
   *
   * The default implementation is CoverageRenderer, but
   * you may implement a renderer with the render technique
   * you want.
   *
   * Several clusters can share the same renderer.
   */
  class PLAB_API Renderer
  {

  protected:
    GLuint _program;

  public:

    Renderer( const Renderer& ) = delete;

    /**
     * Creates the renderer.
     * @param program the identifier of the shader program to use.
     */
    explicit Renderer( GLuint program );

    /**
     * The destructor of the renderer.
     */
    virtual ~Renderer( ) = default;

    /**
     * Renders the given cluster.
     * @param cluster the cluster to render.
     */
    virtual void render( AbstractCluster& cluster ) = 0;
  };
}


#endif //PLAB_RENDERER_H
