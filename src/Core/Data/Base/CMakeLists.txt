set(LIBRARY_NAME DATA_BASE)

#-----------------
# Create INTERFACE library
#-----------------
add_library(${LIBRARY_NAME} INTERFACE)

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} INTERFACE
)

#-----------------
# Include directories
#-----------------
target_include_directories(${LIBRARY_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
