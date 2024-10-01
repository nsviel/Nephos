set(LIBRARY_NAME CORE_DATA)

#-----------------
# Source files
#-----------------
add_subdirectory(Element)
add_subdirectory(Graph)
add_subdirectory(Player)
add_subdirectory(Attribut)
add_subdirectory(Base)
add_subdirectory(Sensor)
add_subdirectory(Texture)

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
  MAIN_CORE

  DATA_ATTRIBUT
  DATA_ELEMENT
  DATA_SCENE
  DATA_PLAYER
  DATA_BASE
  DATA_TEXTURE
  DATA_SENSOR
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
