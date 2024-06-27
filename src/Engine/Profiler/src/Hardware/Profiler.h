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
  void add_queue(prf::hardware::queue::Type type, int ID_family);
  void collect_info(vk::Structure* vk_struct);
  void collect_gpu_info();

private:
  prf::Structure* prf_struct;
  prf::hardware::Collector* prf_collector;

};

}
