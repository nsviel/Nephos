#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/src/Timer/Chrono.h>
#include <Profiler/src/Profiler/Struct_profiler.h>

namespace prf::vulkan{class Device;}
namespace prf::vulkan{class Info;}
namespace prf::vulkan{class Thread;}
namespace prf::graph{class Profiler;}


namespace prf::vulkan{

class Profiler : public prf::type::Profiler
{
public:
  //Constructor / Destructor
  Profiler(string name, string type);
  ~Profiler();

public:
  //Main function

  inline vector<prf::vulkan::Device>& get_info_device(){return vec_device;}
  inline vector<prf::vulkan::Thread>& get_vec_thread(){return vec_thread;}
  inline prf::vulkan::Info* get_info_vulkan(){return info_vulkan;}

private:
  vector<prf::vulkan::Device> vec_device;
  vector<prf::vulkan::Thread> vec_thread;
  prf::vulkan::Info* info_vulkan;
};

}
