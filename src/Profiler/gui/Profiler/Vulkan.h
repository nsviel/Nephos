#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace prf::vulkan{class Profiler;}


namespace prf::gui{

class Vulkan
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

private:
};

}
