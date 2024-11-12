#-----------------
# Python binding
#-----------------
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

pybind11_add_module(nephos_binding
 src/run.cpp
 binding/binding.cpp
)

target_link_libraries(nephos_binding
  PRIVATE MAIN_APPLICATION
)
