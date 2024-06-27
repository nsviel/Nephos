#pragma once

#include <imgui/core/imgui.h>

namespace prf{class Node;}
namespace prf::base{class Profiler;}
namespace prf::hardware{class Profiler;}
namespace prf::hardware{class Device;}
namespace prf::hardware{class Structure;}
namespace prf::gui{class Profiler;}


namespace prf::gui::hardware{

class Device
{
public:
  //Constructor / Destructor
  Device(prf::Node* node_profiler);
  ~Device();

public:
  //Main function
  void draw_tab(prf::hardware::Structure* prf_struct, ImVec2 graph_dim);

  //Subfunction
  void draw_device_info(prf::hardware::Device& device);
  void draw_device_queue_families(prf::hardware::Device& device);

private:
};

}
