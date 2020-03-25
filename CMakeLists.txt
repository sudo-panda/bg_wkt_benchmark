cmake_minimum_required(VERSION 3.0.2)
project (BenchmarkBGwkt)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

find_package(Git REQUIRED)
include(ExternalProject)

ExternalProject_Add(
        Celero
        GIT_REPOSITORY https://github.com/DigitalInBlue/Celero.git
        UPDATE_COMMAND ""
        INSTALL_DIR ${CMAKE_BINARY_DIR}/Celero
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX:STRING=${CMAKE_BINARY_DIR}/Celero
        -DCELERO_COMPILE_DYNAMIC_LIBRARIES:BOOL=OFF
        -DCELERO_ENABLE_EXPERIMENTS:BOOL=OFF
        -DCELERO_ENABLE_FOLDERS:BOOL=OFF)
ExternalProject_Get_Property(Celero SOURCE_DIR)
ExternalProject_Get_Property(Celero INSTALL_DIR)
set(CELERO_INSTALL_DIR ${INSTALL_DIR})

include_directories(${CELERO_INSTALL_DIR}/include)
add_library(libcelero STATIC IMPORTED)
set_property(TARGET libcelero PROPERTY
        IMPORTED_LOCATION_DEBUG
        "${CELERO_INSTALL_DIR}/lib/static/${CMAKE_STATIC_LIBRARY_PREFIX}celerod${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_property(TARGET libcelero PROPERTY
        IMPORTED_LOCATION_RELEASE
        "${CELERO_INSTALL_DIR}/lib/static/${CMAKE_STATIC_LIBRARY_PREFIX}celero${CMAKE_STATIC_LIBRARY_SUFFIX}")
add_dependencies(libcelero Celero)

find_package(Boost 1.73.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include)

add_executable(benchmark_bg_wkt_o2 benchmark.cpp)
set_target_properties(benchmark_bg_wkt_o2 PROPERTIES COMPILE_FLAGS "-O2")
add_dependencies(benchmark_bg_wkt_o2 libcelero)
target_link_libraries(benchmark_bg_wkt_o2 libcelero ${CELERO_EXTRA_LIBS})

add_executable(benchmark_bg_wkt_o3 benchmark.cpp)
set_target_properties(benchmark_bg_wkt_o3 PROPERTIES COMPILE_FLAGS "-O3")
add_dependencies(benchmark_bg_wkt_o3 libcelero)
target_link_libraries(benchmark_bg_wkt_o3 libcelero ${CELERO_EXTRA_LIBS})