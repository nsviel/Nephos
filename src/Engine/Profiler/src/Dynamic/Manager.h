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
  void add_profiler(prf::dynamic::Profiler* profiler);
  void remove_profiler(prf::dynamic::Profiler* profiler);

  //Subfunction
  void loop(int max_fps);

private:
  prf::Structure* prf_struct;
};

}
