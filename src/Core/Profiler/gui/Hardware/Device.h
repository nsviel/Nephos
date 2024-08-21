#pragma once

#include <imgui/core/imgui.h>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::monitor{class Profiler;}
namespace prf::hardware{class Manager;}
namespace prf::hardware{class Structure;}
namespace prf::hardware::structure{class Device;}
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
  void draw_tab();

  //Subfunction
  void draw_device_info(prf::hardware::structure::Device& device);
  void draw_device_queue_families(prf::hardware::structure::Device& device);

private:
  prf::Structure* prf_struct;
};

}
