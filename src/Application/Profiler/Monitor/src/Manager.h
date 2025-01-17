#pragma once

#include <Utility/Namespace.h>
#include <string>
#include <list>

namespace prf::monitor{class Node;}
namespace prf::monitor{class Structure;}
namespace prf::monitor{class Profiler;}
namespace prf::monitor{class Tasker;}
namespace prf::graph{class Profiler;}
namespace vk{class Structure;}


namespace prf::monitor{

class Manager
{
public:
  //Constructor / Destructor
  Manager(prf::monitor::Node* node_monitor);
  ~Manager();

public:
  //Main function
  void init();
  void loop(int max_fps);

  //Subfunction
  void add_profiler(prf::monitor::Profiler* profiler, std::string name);
  void remove_profiler(prf::monitor::Profiler* profiler);
  void collect_gpu_task();
  prf::monitor::Tasker* get_tasker_cpu();

private:
  prf::monitor::Structure* prf_struct;
  vk::Structure* vk_struct;
};

}
