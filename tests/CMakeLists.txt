set(EXECUTABLE_NAME test)

cmake_policy(SET CMP0072 NEW)


#-----------------
# Source files
#-----------------
file(GLOB_RECURSE ALL_SOURCES
  *.cpp
  *.h
)

#-----------------
# Compilation
#-----------------
add_executable(${EXECUTABLE_NAME}
  ${ALL_SOURCES}
  main.cpp
)

#-----------------
# Dependencies
#-----------------
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(${EXECUTABLE_NAME}
  LIBRARY_APPLICATION
  LIBRARY_ENGINE
  LIBRARY_GUI
  LIBRARY_UTILITY
  LIBRARY_DEV
  LIBRARY_VULKAN
  LIBRARY_PROFILER

  OpenGL::OpenGL
)
