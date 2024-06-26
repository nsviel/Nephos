#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Element/Timer/Chrono.h>

namespace prf::base{class Profiler;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}
namespace prf::hardware{class Profiler;}


namespace prf{

class Manager
{
public:
  //Constructor / Destructor
  Manager();
  ~Manager();

public:
  //Main function
  void add_profiler(prf::base::Profiler* profiler);
  void remove_profiler(prf::base::Profiler* profiler);

  //Subfunction
  void loop_begin(int max_fps);
  void loop_end();

  inline prf::graph::Profiler* get_profiler_main(){return profiler_main;}
  inline prf::hardware::Profiler* get_profiler_hardware(){return profiler_hardware;}
  inline std::list<prf::base::Profiler*> get_list_profiler(){return list_profiler;}

private:
  std::list<prf::base::Profiler*> list_profiler;
  prf::graph::Profiler* profiler_main;
  prf::hardware::Profiler* profiler_hardware;
};

}
