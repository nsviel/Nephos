#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/gui/Profiler/Struct_profiler.h>

namespace prf{class Node;}
namespace prf::vulkan{class Profiler;}
namespace prf::vulkan{class Device;}
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

  //Subfunction
  void draw_thread(prf::vulkan::Profiler* prf_vulkan, ImVec2 graph_dim);
  void draw_device(prf::vulkan::Profiler* prf_vulkan, ImVec2 graph_dim);
  void draw_table_info(prf::vulkan::Device& device);
  void draw_table_queue_families(prf::vulkan::Device& device);

private:
};

}
