cmake_minimum_required(VERSION 3.13)
project(projeto-catavento)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "C:/mingw64")

add_executable(projeto-catavento "catavento.cpp")

include_directories(C:/mingw64/include)

target_link_libraries(projeto-catavento -lOpenGL32 -lfreeGLUT -lglu32)
