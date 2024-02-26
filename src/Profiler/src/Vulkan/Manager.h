#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/src/Timer/Chrono.h>
#include <Profiler/src/Profiler/Tasker.h>

namespace prf::vulkan{class Device;}
namespace prf::vulkan{class Info;}
namespace prf::vulkan{class Thread;}
namespace prf{class Tasker;}


namespace prf::vulkan{

class Manager : public prf::Tasker
{
public:
  //Constructor / Destructor
  Manager(string name);
  ~Manager();

public:
  //Main function
  inline vector<prf::vulkan::Device>& get_info_device(){return vec_device;}
  inline prf::vulkan::Info* get_info_vulkan(){return info_vulkan;}
  inline vector<prf::vulkan::Thread>& get_vec_thread(){return vec_thread;}

private:
  vector<prf::vulkan::Device> vec_device;
  vector<prf::vulkan::Thread> vec_thread;
  prf::vulkan::Info* info_vulkan;
};

}
