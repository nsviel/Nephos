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
  void remove_tasker(prf::Tasker* tasker);

  inline prf::Tasker* get_tasker_main(){return tasker_main;}
  inline std::list<prf::Tasker*> get_list_tasker(){return list_tasker;}

private:
  std::list<prf::Tasker*> list_tasker;
  prf::Tasker* tasker_main;
};

}
