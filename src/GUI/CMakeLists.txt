set(LIBRARY_NAME LIBRARY_GUI)

#-----------------
# Source files
#-----------------
add_subdirectory(Dev)
add_subdirectory(Render)
add_subdirectory(Element)
add_subdirectory(Ressource)

file(GLOB_RECURSE ALL_SOURCES
  GUI.cpp
)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_GUI_DEV
  LIBRARY_GUI_RENDER
  LIBRARY_GUI_ELEMENT
  LIBRARY_GUI_RESSOURCE
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
