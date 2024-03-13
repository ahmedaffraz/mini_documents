cmake_minimum_required(VERSION 3.10)
project( Main )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package( OpenCV REQUIRED )
MESSAGE(STATUS "OpenCV found from: ${OpenCV_INSTALL_PATH}") 

# Prefer THREADS library for multi-threading
set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories( ${OpenCV_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
add_executable( Main Main.cpp Stitch_Generator.cpp)
target_link_libraries( Main ${OpenCV_LIBS} )