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

#ifndef PLAB_SKIP_GLEW_INCLUDE

#include <GL/glew.h>

#endif

#include "UniformCache.h"

namespace plab
{
  UniformCache::UniformCache( uint32_t program )
    : _program( program )
    , _cache( )
  {

  }

  int32_t UniformCache::getLocation( const std::string& name )
  {
    auto result = _cache.find( name );
    if ( result == _cache.end( ))
    {
      auto value = glGetUniformLocation( _program , name.c_str( ));
      _cache[ name ] = value;
      return value;
    }
    return result->second;
  }
}
