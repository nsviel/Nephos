#pragma once

namespace prf::hardware{class Node;}
namespace prf::gui::hardware{class Device;}
namespace prf::gui::hardware{class GPU;}
namespace prf::gui::hardware{class CPU;}


namespace prf::gui::hardware{

class Tab
{
public:
  //Constructor / Destructor
  Tab(prf::hardware::Node* node_hardware);
  ~Tab();

public:
  //Main function
  void draw_tab(int width);

  //Subfunction
  void draw_hardware_tabbar();

private:
  prf::gui::hardware::Device* gui_device;
  prf::gui::hardware::GPU* gui_gpu;
  prf::gui::hardware::CPU* gui_cpu;
};

}
