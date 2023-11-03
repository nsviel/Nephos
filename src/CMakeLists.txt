set(EXECUTABLE_NAME executable)

#-----------------
# Source files
#-----------------
add_subdirectory(Application)
add_subdirectory(Element)
add_subdirectory(Engine)
add_subdirectory(GUI)
add_subdirectory(Splatting)

#-----------------
# Compilation
#-----------------
add_executable(executable
  config.h
  main.cpp
)

#-----------------
# Dependencies
#-----------------
target_link_libraries(${EXECUTABLE_NAME}
  LIBRARY_APPLICATION
  LIBRARY_ENGINE
  LIBRARY_GUI
  LIBRARY_ELEMENT
  LIBRARY_SPLATTING
)
