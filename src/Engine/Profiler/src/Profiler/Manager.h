#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/src/Timer/Chrono.h>

namespace prf{class Structure;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}
namespace prf::vulkan{class Profiler;}
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
  void add_profiler(prf::Structure* profiler);
  void remove_profiler(prf::Structure* profiler);

  //Subfunction
  void loop_begin(int max_fps);
  void loop_end();

  inline prf::graph::Profiler* get_profiler_main(){return profiler_main;}
  inline prf::vulkan::Profiler* get_profiler_vulkan(){return profiler_vulkan;}
  inline std::list<prf::Structure*> get_list_profiler(){return list_profiler;}

private:
  std::list<prf::Structure*> list_profiler;
  prf::graph::Profiler* profiler_main;
  prf::vulkan::Profiler* profiler_vulkan;
  prf::hardware::Profiler* profiler_hardware;
};

}
