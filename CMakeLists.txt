cmake_minimum_required(VERSION 3.15)
project(cubic)

set(CMAKE_CXX_STANDARD 14)



if (MINGW)
    set(GLUT_ROOT_PATH ${CMAKE_SOURCE_DIR}/lib/win32/glut)
endif()
#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(SYSTEM ${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARIES})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(SYSTEM ${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

set(EXTRA_LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

include_directories(SYSTEM ../../include/)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
add_custom_target(copy_glut)

add_custom_command(
        TARGET copy_glut PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        -E copy ${CMAKE_SOURCE_DIR}/lib/win32/glut/bin/freeglut.dll
        ${PROJECT_BINARY_DIR}/bin/freeglut.dll
)

add_executable(cubic Application.cpp
        ogl_headers.h CubicApp.cpp CubicApp.h Cubic.cpp Cubic.h CubicWorker.cpp
        CubicWorker.h Face.cpp Face.h  main.cpp)

add_executable(CubeSolver Application.cpp
        ogl_headers.h CubicApp.cpp CubicApp.h Cubic.cpp Cubic.h CubicWorker.cpp
        CubicWorker.h Face.cpp Face.h Menu.cpp Lab8.cpp)
target_link_libraries(cubic ${EXTRA_LIBS})
target_link_libraries(CubeSolver ${EXTRA_LIBS})
if (MINGW)
    target_link_libraries(cubic winmm)
    add_dependencies(cubic copy_glut)
endif()
