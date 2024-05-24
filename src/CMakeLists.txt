set(EXECUTABLE_NAME executable)

#-----------------
# Source files
#-----------------
add_subdirectory(Application)
add_subdirectory(Utility)
add_subdirectory(Module)
add_subdirectory(Engine)
add_subdirectory(Vulkan)

#-----------------
# Compilation
#-----------------
add_executable(${EXECUTABLE_NAME}
  main.cpp
)

#-----------------
# Dependencies
#-----------------
target_link_libraries(${EXECUTABLE_NAME}
  LIBRARY_APPLICATION
)
