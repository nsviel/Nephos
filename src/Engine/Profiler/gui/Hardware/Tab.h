#pragma once

namespace prf{class Node;}
namespace prf::base{class Profiler;}
namespace prf::hardware{class Profiler;}
namespace prf::hardware{class Device;}
namespace prf::hardware{class Structure;}
namespace prf::gui{class Profiler;}
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
  void draw_subtab();
  
private:
  prf::gui::hardware::Device* gui_device;
  prf::gui::hardware::GPU* gui_gpu;
};

}
