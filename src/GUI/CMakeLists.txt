set(LIBRARY_NAME LIBRARY_GUI)

#-----------------
# Source files
#-----------------
add_subdirectory(TAB_dev)
add_subdirectory(TAB_render)
add_subdirectory(GUI_main)
add_subdirectory(GUI_utility)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC
  GUI_nsp.h
)

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN
  LIBRARY_UTILITY
  LIBRARY_ENGINE

  LIBRARY_GUI_MAIN
  LIBRARY_GUI_UTILITY
  LIBRARY_GUI_TAB_DEV
  LIBRARY_GUI_TAB_RENDER
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
