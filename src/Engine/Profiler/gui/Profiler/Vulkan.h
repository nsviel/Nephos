#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace prf::base{class Profiler;}
namespace prf::vulkan{class Profiler;}
namespace prf::vulkan{class Device;}
namespace prf::vulkan{class Structure;}
namespace prf::gui{class Profiler;}


namespace prf::gui{

class Vulkan
{
public:
  //Constructor / Destructor
  Vulkan(prf::Node* node_profiler);
  ~Vulkan();

public:
  //Main function
  void show_profiler(prf::base::Profiler* profiler);

  //Tab function
  void draw_info(prf::vulkan::Structure* prf_struct);
  void draw_tab(prf::vulkan::Structure* prf_struct);
  void draw_tab_thread(prf::vulkan::Structure* prf_struct, ImVec2 graph_dim);
  void draw_tab_queue(prf::vulkan::Structure* prf_struct, ImVec2 graph_dim);
  void draw_tab_device(prf::vulkan::Structure* prf_struct, ImVec2 graph_dim);

  //Subfunction
  void draw_device_info(prf::vulkan::Device& device);
  void draw_device_queue_families(prf::vulkan::Device& device);

private:
};

}
