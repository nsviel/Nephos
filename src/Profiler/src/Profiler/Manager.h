#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/src/Timer/Chrono.h>

namespace prf{class Tasker;}


namespace prf{

class Manager
{
public:
  //Constructor / Destructor
  Manager();
  ~Manager();

public:
  //Main function
  inline prf::Tasker* get_tasker_cpu(){return tasker_cpu;}
  inline prf::Tasker* get_tasker_gpu(){return tasker_gpu;}
  inline prf::Tasker* get_tasker_cap(){return tasker_cap;}

private:
  prf::Tasker* tasker_cpu;
  prf::Tasker* tasker_gpu;
  prf::Tasker* tasker_cap;
};

}
