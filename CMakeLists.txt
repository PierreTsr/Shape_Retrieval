project(shape_retrieval)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# libigl
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)

find_package(LIBIGL REQUIRED QUIET)
find_package( OpenCV REQUIRED )
find_package( OpenMP )
find_package( PythonLibs )

if( PYTHONLIBS_FOUND)
    include_directories( ${PYTHON_INCLUDE_DIR} )
endif(PYTHONLIBS_FOUND)

if( OpenCV_FOUND )
    list( APPEND ThirdParty_LIBS ${OpenCV_LIBS} )
    include_directories( ${OpenCV_INCLUDE_DIRS} )
endif( OpenCV_FOUND )
find_package( Boost )
include_directories(external/dkm)

find_package( Boost )
file(GLOB SRCFILES src/*.cpp)
add_executable(ex_bin ${SRCFILES})

target_link_libraries( ex_bin ${OpenCV_LIBS} )
target_link_libraries(ex_bin igl::core igl::opengl_glfw)

target_compile_options(ex_bin PRIVATE ${OpenMP_CXX_FLAGS})
target_link_libraries(ex_bin  ${OpenMP_CXX_LIBRARIES})

target_link_libraries(ex_bin ${Boost_LIBRARIES})

target_link_libraries(ex_bin ${PYTHON_LIBRARY} )
