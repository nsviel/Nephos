#-----------------
# Project
#-----------------
cmake_minimum_required(VERSION 3.5)
project(NEPHOS LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")
set(CMAKE_BUILD_TYPE Release)
set(EXECUTABLE_NAME executable)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#-----------------
# Source files
#-----------------
add_subdirectory(extern)
add_subdirectory(src)
#add_subdirectory(binding)

#-----------------
# Executable
#-----------------
add_executable(${EXECUTABLE_NAME}
  src/main.cpp
)

target_link_libraries(${EXECUTABLE_NAME}
  PRIVATE MAIN_APPLICATION
)
