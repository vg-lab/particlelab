# Define public headers
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
  gl/SimpleRenderer.h
  reto/CameraModel.h
  reto/RetoCamera.h
)

# Create the includes strings for the unified header
set(HEADER_INCLUDES "")
foreach(header ${PLAB_PUBLIC_HEADERS})
  string(APPEND HEADER_INCLUDES "#include <${PROJECT_NAME}/${header}>\n")
endforeach()

# Generate the unified header
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/unified_header.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.h"
)

# Get the current Git commit for the version header
find_package(Git)
if(Git_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} --no-pager log -n 1 HEAD "--pretty=format:%h"
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    RESULT_VARIABLE git_result
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(git_result EQUAL 0)
    message(STATUS "Last ${PROJECT_NAME} Git commit: ${GIT_COMMIT_HASH}")
  endif()
endif()

# Generate the version header
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h"
)

# Define source files
set(PLAB_SOURCES
  core/AbstractCluster.cpp
  core/Renderer.cpp
  core/UniformCache.cpp
  core/Updater.cpp
  particle/BasicParticle.cpp
  particle/Particle.cpp
  gl/CoverageRenderer.cpp
  gl/SimpleRenderer.cpp
  reto/CameraModel.cpp
  reto/RetoCamera.cpp
)

# Create the target
add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Generate export header
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

# Add sources to the target
target_sources(${PROJECT_NAME}
  PRIVATE
    ${PLAB_SOURCES}
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS
      ${PROJECT_SOURCE_DIR}
    FILES
      ${PLAB_PUBLIC_HEADERS}
)

target_sources(${PROJECT_NAME}
  PUBLIC
    FILE_SET public_headers_generated
    TYPE HEADERS
    BASE_DIRS
      ${PROJECT_BINARY_DIR}
    FILES
      # Generated headers
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}.h
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}_export.h
      ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

# Add compile definitions
target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    $<$<BOOL:${PLAB_SKIP_GLEW_INCLUDE}>:PLAB_SKIP_GLEW_INCLUDE>
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    OpenGL::GL
    GLEW::GLEW
    glm::glm
    ReTo::ReTo
)