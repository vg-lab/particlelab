# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   Plab
#   2014-2022 (c) GMRV / Universidad Rey Juan Carlos
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(plab VERSION 0.1.1)
set(plab_VERSION_ABI 6)

# Disable in source building
if ("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL "no in source building allowed.")
endif ()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
        ${CMAKE_SOURCE_DIR}/CMake/common)

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/CMake/common/Common.cmake)
    message(FATAL_ERROR "CMake/common missing, run: git submodule update --init")
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
endif ()

include(GitExternal)

set(PLAB_DESCRIPTION "PLAB - Particle Framework")
set(COMMON_PROJECT_DOMAIN gmrv.es)

option(PLAB_WITH_OPENSCENEGRAPH "PLAB_WITH_OPENSCENEGRAPH" OFF)
#option( PLAB_WITH_CUDA "PLAB_WITH_CUDA" OFF )
option(MODERN_GPU_ARCH "GPU_ARCH" ON)
option(PLAB_WITH_EXAMPLES "PLAB_WITH_EXAMPLES" OFF)
option(PLAB_WITH_LOGGING "PLAB_WITH_LOGGING" OFF)
option(PLAB_PARALLEL "PLAB_PARALLEL" ON)

if (PLAB_WITH_LOGGING)
    add_definitions(-DPLAB_WITH_LOGGING)
endif ()

include(Common)

#common_find_package( nvidiaOpenGL SYSTEM )
common_find_package(OpenGL REQUIRED SYSTEM)
common_find_package(GLEW REQUIRED SYSTEM)
common_find_package(GLM REQUIRED SYSTEM)
common_find_package(GLUT SYSTEM)
common_find_package(Boost REQUIRED)
common_find_package(Eigen3 SYSTEM)
common_find_package(ReTo REQUIRED)

list(APPEND PLAB_DEPENDENT_LIBRARIES ReTo OpenGL GLEW GLM Boost)

if (GLUT_FOUND)
    list(APPEND PLAB_DEPENDENT_LIBRARIES GLUT)
endif ()

if (PLAB_PARALLEL)
    common_find_package(OpenMP)
    if (OPENMP_FOUND)
        list(APPEND PLAB_DEPENDENT_LIBRARIES OpenMP)
    endif ()
endif ()


if (PLAB_WITH_OPENSCENEGRAPH)
    common_find_package(OpenSceneGraph 3.2 EXACT COMPONENTS
            osgViewer osgGA osgDB osgUtil osgQt SYSTEM)
    if (OPENSCENEGRAPH_FOUND)
        list(APPEND PLAB_DEPENDENT_LIBRARIES OpenSceneGraph)
    endif ()
endif ()

if (PLAB_WITH_CUDA)
    include(CudaCommonLibrary)
    find_package(CUDA REQUIRED)
    common_find_package(CUDA SYSTEM REQUIRED)
    if (CUDA_FOUND)
        list(APPEND PLAB_DEPENDENT_LIBRARIES CUDA)

        common_find_package(CUDAThrust SYSTEM)
        if (CUDAThrust_FOUND)
            list(APPEND PLAB_DEPENDENT_LIBRARIES CUDAThrust)
        endif ()
    endif ()
endif ()

common_find_package_post()

set(PLAB_LIBRARY_BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/plab)

add_subdirectory(plab)

add_subdirectory(examples)

include(CPackConfig)
include(DoxygenRule)
