#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/gui/Profiler/Struct_profiler.h>

namespace prf{class Node;}
namespace prf::vulkan{class Profiler;}
namespace prf::vulkan{class Device;}
namespace prf::vulkan{class Structure;}
namespace prf::gui{class Profiler;}


namespace prf::gui{

class Vulkan : public prf::gui::Profiler
{
public:
  //Constructor / Destructor
  Vulkan(prf::Node* node_profiler);
  ~Vulkan();

public:
  //Main function
  void draw_profiler(prf::vulkan::Profiler* prf_vulkan);

  //Tab function
  void draw_tab_thread(prf::vulkan::Structure* prf_struct, ImVec2 graph_dim);
  void draw_tab_queue(prf::vulkan::Structure* prf_struct, ImVec2 graph_dim);
  void draw_tab_device(prf::vulkan::Structure* prf_struct, ImVec2 graph_dim);

  //Subfunction
  void draw_device_info(prf::vulkan::Device& device);
  void draw_device_queue_families(prf::vulkan::Device& device);
  std::string get_selected_gpu_name(prf::vulkan::Profiler* prf_vulkan);

private:
};

}
