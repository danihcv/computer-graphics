cmake_minimum_required(VERSION 3.13)
project(projeto-house)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "C:/mingw64")

add_executable(projeto-house "house")

include_directories(C:/mingw64/include)

target_link_libraries(projeto-house -lOpenGL32 -lfreeGLUT -lglu32)
