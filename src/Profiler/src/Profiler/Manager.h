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
  prf::Tasker* new_tasker(string name, string type);

  inline prf::Tasker* get_tasker_main(){return tasker_main;}
  inline vector<prf::Tasker*> get_vec_tasker(){return vec_tasker;}

private:
  vector<prf::Tasker*> vec_tasker;
  prf::Tasker* tasker_main;
  prf::Tasker* tasker_cap;
};

}
