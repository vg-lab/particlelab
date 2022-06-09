# ParticleLab - Particle Rendering Next Generation
(c) 2022-2022. VG-Lab / URJC

www.vg-lab.es
gmrv@gmrv.es

## Introduction

ParticleLab is a GPU-centric framework that allows
the developer to create particle clusters that can
be modified over time using compute shaders, sending
only the required information to the GPU.

## Dependencies

### Strong dependences:

* OpenGL
* GLEW
* GLM
* ReTo (*)

(*) Note: These dependencies will be automatically downloaded and compiled with
the project.

### Weak dependences

* OpenMP: multi-core functioning. 
* GLUT: OpenGL example.
* Eigen3: full ReTo compatibility

## Building

ParticleLab has been successfully built with GCC 9.4.0 and used on Ubuntu 20.04 
and Windows 10/11 (Visual Studio 2022 Win64).
The following steps should be enough to build it:

```bash
git clone https://gitlab.gmrv.es/g.rial/particlelab.git particlelab
mkdir particlelab/build && cd particlelab/build
cmake .. -DCMAKE_BUILD_TYPE=Release -DPLAB_WITH_EXAMPLES=ON
make
```