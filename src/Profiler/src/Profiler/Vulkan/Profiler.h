#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/src/Timer/Chrono.h>
#include <Profiler/src/Profiler/Struct_profiler.h>
#include <Profiler/src/Profiler/Vulkan/Struct_info.h>

namespace prf::vulkan{class Device;}
namespace prf::vulkan{class Info;}
namespace prf::vulkan{class Thread;}
namespace prf::vulkan{class Queue;}
namespace prf::type{class Profiler;}


namespace prf::vulkan{

class Profiler : public prf::type::Profiler
{
public:
  //Constructor / Destructor
  Profiler(string name, string type);
  ~Profiler();

public:
  //Main function
  void add_thread(string name);
  void add_queue(prf::vulkan::Queue_type type, int ID_family);

  inline vector<prf::vulkan::Device>& get_info_device(){return vec_device;}
  inline vector<prf::vulkan::Thread>& get_vec_thread(){return vec_thread;}
  inline map<prf::vulkan::Queue_type, prf::vulkan::Queue>& get_map_queue(){return map_queue;}
  inline prf::vulkan::Info* get_info(){return info;}

private:
  vector<prf::vulkan::Device> vec_device;
  vector<prf::vulkan::Thread> vec_thread;
  map<prf::vulkan::Queue_type, prf::vulkan::Queue> map_queue;
  prf::vulkan::Info* info;

  std::mutex mutex;
};

}
