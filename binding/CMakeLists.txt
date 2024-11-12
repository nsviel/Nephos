#-----------------
# Python binding
#-----------------
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

pybind11_add_module(pynephos
 ../src/App.cpp
 binding.cpp
)

set_target_properties(pynephos PROPERTIES
  LIBRARY_OUTPUT_NAME "pynephos"
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  #LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../binding
)

target_link_libraries(pynephos
  PRIVATE MAIN_APPLICATION
)
