set(LIBRARY_NAME CORE_IO)

#-----------------
# Source files
#-----------------
add_subdirectory(Exporter)
add_subdirectory(Importer)
add_subdirectory(Format)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} INTERFACE)

#-----------------
# Set include directories
#-----------------
target_include_directories(${LIBRARY_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)

#-----------------
# Link dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} INTERFACE
  IO_EXPORTER
  IO_IMPORTER
  IO_FORMAT
)
