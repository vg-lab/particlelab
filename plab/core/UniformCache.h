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

#ifndef PLAB_UNIFORMCACHE_H
#define PLAB_UNIFORMCACHE_H

#include <plab/api.h>

#include <map>

namespace plab
{

  /**
   * Util class used to cache the uniforms' locations of a shader program.
   */
  class PLAB_API UniformCache
  {

    uint32_t _program;
    std::map< std::string , int32_t > _cache;

  public:

    /**
     * Creates a new cache.
     * @param program the shader program used by this cache.
     */
    explicit UniformCache( uint32_t program );

    /**
     * Returns the location of the uniform with the given name.
     * @param name the name.
     * @return the location or -1 if not found.
     */
    int32_t getLocation( const std::string& name );

  };
}


#endif //PLAB_UNIFORMCACHE_H
