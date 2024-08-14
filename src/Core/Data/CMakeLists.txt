set(LIBRARY_NAME CORE_DATA)

#-----------------
# Source files
#-----------------
add_subdirectory(Element)
add_subdirectory(Graph)

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
  DATA_ELEMENT
  DATA_GRAPH
)
