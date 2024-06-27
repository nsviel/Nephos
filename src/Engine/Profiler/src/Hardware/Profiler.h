#pragma once

#include <Profiler/src/Hardware/Structure/Queue.h>
#include <Profiler/src/Hardware/Structure/Structure.h>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::hardware{class Device;}
namespace prf::hardware{class Thread;}
namespace prf::hardware{class Queue;}
namespace prf::hardware{class Collector;}
namespace prf::base{class Profiler;}
namespace vk{class Structure;}


namespace prf::hardware{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(prf::Node* node_profiler);
  ~Profiler();

public:
  //Main function
  void init();
  void loop();

private:
  prf::Structure* prf_struct;
  prf::hardware::Collector* prf_collector;

};

}
