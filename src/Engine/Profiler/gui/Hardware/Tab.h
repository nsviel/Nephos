#pragma once

namespace prf{class Node;}
namespace prf::gui::hardware{class Device;}
namespace prf::gui::hardware{class GPU;}


namespace prf::gui::hardware{

class Tab
{
public:
  //Constructor / Destructor
  Tab(prf::Node* node_profiler);
  ~Tab();

public:
  //Main function
  void draw_tab();

  //Subfunction
  void draw_hardware_tabbar();

private:
  prf::gui::hardware::Device* gui_device;
  prf::gui::hardware::GPU* gui_gpu;
};

}
