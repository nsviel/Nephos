#pragma once

#include <Utility/Element/Timer/Chrono.h>
#include <list>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::dynamic{class Profiler;}
namespace prf::dynamic{class Tasker;}
namespace prf::graph{class Profiler;}


namespace prf::dynamic{

class Manager
{
public:
  //Constructor / Destructor
  Manager(prf::Node* node_profiler);
  ~Manager();

public:
  //Main function
  void init();
  void loop(int max_fps);

  //Subfunction
  void add_profiler(prf::dynamic::Profiler* profiler);
  void remove_profiler(prf::dynamic::Profiler* profiler);
  prf::dynamic::Tasker* get_tasker_cpu();
  prf::dynamic::Tasker* get_tasker_gpu();

private:
  prf::Structure* prf_struct;
};

}
