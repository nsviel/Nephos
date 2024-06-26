#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Element/Timer/Chrono.h>
#include <Profiler/src/Base/Profiler.h>
#include <Profiler/src/Hardware/Structure/Queue.h>
#include <Profiler/src/Hardware/Structure/Structure.h>

namespace prf::hardware{class Device;}
namespace prf::hardware{class Thread;}
namespace prf::hardware{class Queue;}
namespace prf::hardware{class Collector;}
namespace prf::base{class Profiler;}
namespace vk::structure{class Vulkan;}


namespace prf::hardware{

class Profiler : public prf::base::Profiler
{
public:
  //Constructor / Destructor
  Profiler();
  ~Profiler();

public:
  //Main function
  void add_queue(prf::hardware::queue::Type type, int ID_family);
  void collect_info(vk::structure::Vulkan* vk_struct);
  void collect_gpu_info();

  inline prf::hardware::Structure* get_prf_struct(){return prf_struct;}

private:
  prf::hardware::Collector* prf_collector;
  prf::hardware::Structure* prf_struct;
};

}
