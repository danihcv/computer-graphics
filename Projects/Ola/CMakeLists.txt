cmake_minimum_required(VERSION 3.13)
project(projeto-ola)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "C:/mingw64")

add_executable(projeto-ola "ola.cpp")

include_directories(C:/mingw64/include)

target_link_libraries(projeto-ola -lOpenGL32 -lfreeGLUT -lglu32)
