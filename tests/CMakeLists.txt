set(EXECUTABLE_NAME test)

#-----------------
# Source files
#-----------------
file(GLOB_RECURSE ALL_SOURCES
  *.cpp
)

#-----------------
# Compilation
#-----------------
add_executable(${EXECUTABLE_NAME}
  main.cpp
)
