#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/src/Timer/Chrono.h>

namespace prf{class Tasker;}
namespace prf{class Profiler;}
namespace prf::vulkan{class Profiler;}


namespace prf{

class Manager
{
public:
  //Constructor / Destructor
  Manager();
  ~Manager();

public:
  //Main function
  prf::Profiler* new_profiler(string name, string type);
  void new_profiler(prf::Profiler* profiler);
  void remove_profiler(prf::Profiler* profiler);

  inline prf::Profiler* get_profiler_main(){return profiler_main;}
  inline prf::vulkan::Profiler* get_profiler_vulkan(){return profiler_vulkan;}
  inline std::list<prf::Profiler*> get_list_profiler(){return list_profiler;}

private:
  std::list<prf::Profiler*> list_profiler;
  prf::Profiler* profiler_main;
  prf::vulkan::Profiler* profiler_vulkan;
};

}
