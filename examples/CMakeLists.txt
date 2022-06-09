if (PLAB_WITH_EXAMPLES)

    include_directories(${CMAKE_CURRENT_BINARY_DIR})

    if (GLUT_FOUND)

        set(EXAMPLESCENE_HEADERS)
        set(EXAMPLESCENE_SOURCES exampleScene.cpp)
        set(EXAMPLESCENE_LINK_LIBRARIES plab)
        common_application(ExampleScene)

    endif (GLUT_FOUND)


endif ()
