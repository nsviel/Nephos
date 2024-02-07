#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/src/Timer/Chrono.h>


namespace prf{

class Manager
{
public:
  //Constructor / Destructor
  Manager();
  ~Manager();

public:
  //Main function


  inline string get_gpu_dev(){return gpu_dev;}

private:
  string gpu_dev;
};

}
