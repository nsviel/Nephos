set(LIBRARY_NAME LIBRARY_D455)

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
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_ENGINE
  LIBRARY_UTILITY
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
