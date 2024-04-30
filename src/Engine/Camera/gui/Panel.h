#pragma once

#include <Utility/Specific/Common.h>
#include <glm/glm.hpp>

namespace cam{class Node;}
namespace cam{class Control;}
namespace cam{class Manager;}


namespace cam::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(cam::Node* node_camera, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void cam_parameter();
  void cam_info();
  void cam_definedPosition();

private:
  cam::Control* cam_control;
  cam::Manager* cam_manager;

  int item_width;
  bool* show_window;
  string name;
};

}
