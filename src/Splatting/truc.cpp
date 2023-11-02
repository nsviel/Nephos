#include <Python.h>


int main_python() {
  // Initialize the Python interpreter
  Py_Initialize();

  // Execute a Python script
  const char* pythonScript = "print('Hello, World! from Python')";
  PyRun_SimpleString(pythonScript);

  // Finalize the Python interpreter
  Py_Finalize();

  return 0;
}
