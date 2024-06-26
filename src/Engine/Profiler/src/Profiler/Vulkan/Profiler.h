#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/src/Timer/Chrono.h>
#include <Profiler/src/Profiler/Base/Profiler.h>
#include <Profiler/src/Profiler/Vulkan/Structure/Queue.h>
#include <Profiler/src/Profiler/Vulkan/Structure/Structure.h>

namespace prf::vulkan{class Device;}
namespace prf::vulkan{class Thread;}
namespace prf::vulkan{class Queue;}
namespace prf::vulkan{class Collector;}
namespace prf::base{class Profiler;}
namespace vk::structure{class Vulkan;}


namespace prf::vulkan{

class Profiler : public prf::base::Profiler
{
public:
  //Constructor / Destructor
  Profiler();
  ~Profiler();

public:
  //Main function
  void add_thread(string name);
  void add_queue(prf::vulkan::queue::Type type, int ID_family);
  void collect_info(vk::structure::Vulkan* vk_struct);

  inline prf::vulkan::Structure* get_prf_struct(){return prf_struct;}

private:
  prf::vulkan::Collector* prf_collector;
  prf::vulkan::Structure* prf_struct;
};

}
