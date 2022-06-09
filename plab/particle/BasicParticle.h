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
// Created by gaeqs on 9/06/22.
//

#ifndef PLAB_BASICPARTICLE_H
#define PLAB_BASICPARTICLE_H

#include <plab/api.h>

#include <glm/vec3.hpp>

/**
 * A basic particle, containing only a position.
 */
struct PLAB_API BasicParticle
{
  glm::vec3 position;

  static void enableVAOAttributes( );

};


#endif //PLAB_BASICPARTICLE_H
