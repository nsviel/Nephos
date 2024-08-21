#pragma once

namespace prf::hardware{class Node;}
namespace prf::hardware{class Structure;}
namespace prf::hardware::structure{class Device;}


namespace prf::gui::hardware{

class Device
{
public:
  //Constructor / Destructor
  Device(prf::hardware::Node* node_hardware);
  ~Device();

public:
  //Main function
  void draw_tab();

  //Subfunction
  void draw_device_info(prf::hardware::structure::Device& device);
  void draw_device_queue_families(prf::hardware::structure::Device& device);

private:
  prf::hardware::Structure* prf_struct;
};

}
