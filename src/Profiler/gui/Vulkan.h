#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace prf::vulkan{class Manager;}


namespace prf::gui{

class Vulkan
{
public:
  //Constructor / Destructor
  Vulkan(prf::Node* node_profiler);
  ~Vulkan();

public:
  //Main function
  void draw_graph(prf::vulkan::Manager* prf_vulkan);

  //Profiler
  void draw_profiler(prf::vulkan::Manager* prf_vulkan, ImVec2 graph_dim);

private:
};

}
