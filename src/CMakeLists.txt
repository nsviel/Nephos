set(EXECUTABLE_NAME executable)

#-----------------
# Source files
#-----------------
add_subdirectory(Application)
add_subdirectory(Core)
add_subdirectory(Dynamic)
add_subdirectory(Module)
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
  MAIN_APPLICATION
)
