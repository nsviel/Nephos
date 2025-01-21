set(PACKAGE_NAME pynephos)

#-----------------
# Python binding
#-----------------
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

pybind11_add_module(${PACKAGE_NAME}
  ../../src/Application/Interface/App.cpp
  binding.cpp
)

set_target_properties(${PACKAGE_NAME} PROPERTIES
  LIBRARY_OUTPUT_NAME "pynephos"
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  #LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../binding
)

target_link_libraries(${PACKAGE_NAME}
  PRIVATE MAIN_APPLICATION
)
