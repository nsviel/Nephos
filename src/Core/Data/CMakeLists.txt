set(LIBRARY_NAME CORE_DATA)

#-----------------
# Source files
#-----------------
add_subdirectory(Element)
add_subdirectory(Graph)
add_subdirectory(Player)
add_subdirectory(Attribut)

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
target_link_libraries(${LIBRARY_NAME} PUBLIC
  DATA_ATTRIBUT
  DATA_ELEMENT
  DATA_GRAPH
  DATA_PLAYER
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
