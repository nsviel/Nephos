set(LIBRARY_NAME CORE_IO)

#-----------------
# Source files
#-----------------
add_subdirectory(Exporter)
add_subdirectory(Importer)
add_subdirectory(Format)
add_subdirectory(Transformation)

file(GLOB_RECURSE ALL_SOURCES
  Node.cpp
)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
find_package(HDF5 REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_UTILITY
  LIBRARY_CORE
  IO_IMPORTER
  IO_EXPORTER
  IO_TRANSFORMATION
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
