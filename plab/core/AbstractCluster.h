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

#ifndef PLAB_ABSTRACTCLUSTER_H
#define PLAB_ABSTRACTCLUSTER_H

#include <plab/api.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include <memory>

namespace plab
{

  class Renderer;

  class Model;

  class Updater;

  /**
   * A cluster that doesn't define a particle type.
   *
   * It is not recommended to use this implementation.
   * Use the Cluster class instead.
   */
  class PLAB_API AbstractCluster
  {

    std::shared_ptr< Renderer > _renderer;
    std::shared_ptr< Model > _model;
    std::shared_ptr< Updater > _updater;

    GLuint _vaoBuffer;
    GLuint _vertexBuffer;
    GLuint _dataBuffer;

    uint32_t _size;

  public:

    AbstractCluster( const AbstractCluster& ) = delete;

    /**
     * Creates the cluster.
     * This constructor also creates all required OpenGL objects.
     */
    AbstractCluster( );

    /**
     * The destructor of the cluster.
     * This destructor also destroys all underlying OpenGL objects.
     */
    virtual ~AbstractCluster( );

    /**
     * Returns the identifier of the underlying VAO.
     * @return the identifier of the VAO.
     */
    GLuint getVaoBuffer( ) const;

    /**
     * Returns the identifier of the underlying vertex buffer.
     * @return the identifier of the vertex buffer.
     */
    GLuint getVertexBuffer( ) const;

    /**
     * Returns the identifier of the underlying data buffer.
     * @return the identifier of the data buffer.
     */
    GLuint getDataBuffer( ) const;

    /**
     * Returns the render used by this cluster.
     * @return the render.
     */
    const std::shared_ptr< Renderer >& getRenderer( ) const;

    /**
     * Sets the render used by this cluster.
     *
     * @param renderer the render.
     */
    void setRenderer( const std::shared_ptr< Renderer >& renderer );

    /**
     * Returns the model used by this cluster.
     * @return the model.
     */
    const std::shared_ptr< Model >& getModel( ) const;

    /**
     * Sets the model used by this cluster.
     * @param model the model.
     */
    void setModel( const std::shared_ptr< Model >& model );

    /**
     * Returns the updater of this cluster.
     * @return the updater.
     */
    const std::shared_ptr< Updater >& getUpdater( ) const;

    /**
     * Sets the updater of this cluster.
     * @param updater the updater.
     */
    void setUpdater( const std::shared_ptr< Updater >& updater );

    /**
     * Returns the amount of particles inside this cluster.
     * @return the amount of particles.
     */
    uint32_t size( ) const;

    /**
     * Returns the size in bytes of each particle.
     * @return the size in bytes of each particle.
     */
    virtual uint64_t particleSize( ) const = 0;

    /**
     * Binds the underlying VAO.
     */
    void bindVAO( );

    /**
     * Updates the particles using this cluster's updater.
     */
    void update( );

    /**
     * Renders the particles using this cluster's model and renderer.
     */
    void render( );

    /**
     * Clears the data buffer and resizes it
     * to hold the given amount of particles.
     *
     * @param particles the amount of particles to hold.
     */
    void allocateBuffer( GLsizeiptr particles );

    /**
     * Unmaps the data buffer.
     *
     * Any pointer of the mapped buffer will
     * be marked as unavailable. You mustn't
     * use them after this method's invocation.
     */
    void unmapData( );

  protected:

    void setParticlesRaw( void* data , GLsizeiptr amount );

    void* mapDataRaw( );

  };

}

#endif //PLAB_ABSTRACTCLUSTER_H
