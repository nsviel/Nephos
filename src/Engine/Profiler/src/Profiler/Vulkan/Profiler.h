#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/src/Timer/Chrono.h>
#include <Profiler/src/Profiler/Base/Profiler.h>
#include <Profiler/src/Profiler/Vulkan/Structure/Queue.h>
#include <Profiler/src/Profiler/Vulkan/Structure/Info.h>

namespace prf::vulkan{class Device;}
namespace prf::vulkan{class Thread;}
namespace prf::vulkan{class Queue;}
namespace prf::vulkan{class Collector;}
namespace prf::base{class Profiler;}


namespace prf::vulkan{

class Profiler : public prf::base::Profiler
{
public:
  //Constructor / Destructor
  Profiler();
  Profiler(string name, string type);
  ~Profiler();

public:
  //Main function
  void add_thread(string name);
  void add_queue(prf::vulkan::queue::Type type, int ID_family);

  inline prf::vulkan::Collector* get_prf_collector(){return prf_collector;}
  inline vector<prf::vulkan::Thread>& get_vec_thread(){return vec_thread;}
  inline map<prf::vulkan::queue::Type, prf::vulkan::Queue>& get_map_queue(){return map_queue;}

private:
  prf::vulkan::Collector* prf_collector;
  prf::vulkan::Info* prf_info;
  std::vector<prf::vulkan::Thread> vec_thread;
  std::vector<prf::vulkan::Device> vec_device;
  std::map<prf::vulkan::queue::Type, prf::vulkan::Queue> map_queue;
  std::mutex mutex;
};

}
