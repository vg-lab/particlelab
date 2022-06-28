source_group(\\ FILES CMakeLists.txt)

set(PLAB_PUBLIC_HEADERS
        core/AbstractCluster.h
        core/Cluster.h
        core/Renderer.h
        core/Model.h
        core/UniformCache.h
        core/ICamera.h
        core/Updater.h

        particle/BasicParticle.h
        particle/Particle.h

        gl/CoverageRenderer.h

        reto/CameraModel.h
        reto/RetoCamera.h
        )

set(PLAB_HEADERS)

set(PLAB_SOURCES
        core/AbstractCluster.cpp
        core/Renderer.cpp
        core/UniformCache.cpp
        core/Updater.cpp

        particle/BasicParticle.cpp
        particle/Particle.cpp

        gl/CoverageRenderer.cpp

        reto/CameraModel.cpp
        reto/RetoCamera.cpp
        )

set(PLAB_LINK_LIBRARIES
        ReTo
        ${GLEW_LIBRARIES}
        ${BOOST_LIBRARIES}
        )

add_definitions(-DPLAB_SHARED)

if (GLUT_FOUND)
    set(PLAB_LINK_LIBRARIES ${PLAB_LINK_LIBRARIES} ${GLUT_LIBRARIES})
endif ()

if (NVIDIAOPENGL_FOUND)
    link_directories(${NVIDIA_OPENGL_gl_LIBRARY_PATH})
    set(PLAB_LINK_LIBRARIES ${PLAB_LINK_LIBRARIES} ${NVIDIA_OPENGL_gl_LIBRARY})
else ()
    set(PLAB_LINK_LIBRARIES ${PLAB_LINK_LIBRARIES} ${OPENGL_LIBRARIES})
endif ()

if (OPENSCENEGRAPH_FOUND)
    set(PLAB_LINK_LIBRARIES ${PLAB_LINK_LIBRARIES} ${OPENSCENEGRAPH_LIBRARIES})
endif ()

set(PLAB_INCLUDE_NAME plab)
set(PLAB_NAMESPACE plab)

common_library(plab)
