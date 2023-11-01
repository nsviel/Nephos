cmake_minimum_required(VERSION 3.0)

project(MyProject)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")


# Set up cross-compilation environment
  set(CMAKE_SYSTEM_NAME Windows)
  set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc-posix)
  set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++-posix)
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_AR x86_64-w64-mingw32-ar)
  set(CMAKE_RANLIB x86_64-w64-mingw32-ranlib)

# Add cross-compiled GLFW library and header files
include_directories(glfw)
link_directories(glfw)

# Add your project's source files
add_executable(MyExecutable main.cpp)

# Link against GLFW
target_link_libraries(MyExecutable -lglfw3 -lwinpthread)
