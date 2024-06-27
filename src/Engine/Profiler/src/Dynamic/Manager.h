#pragma once

#include <Utility/Element/Timer/Chrono.h>
#include <list>

namespace prf::dynamic{class Profiler;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}


namespace prf{

class Manager
{
public:
  //Constructor / Destructor
  Manager();
  ~Manager();

public:
  //Main function
  void add_profiler(prf::dynamic::Profiler* profiler);
  void remove_profiler(prf::dynamic::Profiler* profiler);

  //Subfunction
  void loop_begin(int max_fps);
  void loop_end();

  inline prf::graph::Profiler* get_profiler_main(){return profiler_main;}
  inline std::list<prf::dynamic::Profiler*> get_list_profiler(){return list_profiler;}

private:
  std::list<prf::dynamic::Profiler*> list_profiler;
  prf::graph::Profiler* profiler_main;
};

}
