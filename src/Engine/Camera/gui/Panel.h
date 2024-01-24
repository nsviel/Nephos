#pragma once

#include <Utility/Base/GUI/Panel.h>
#include <Utility/Specific/common.h>

class Panel;
namespace eng::cam{class Node;}
namespace eng::cam{class Control;}
namespace eng::cam{class Manager;}


namespace eng::cam::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(eng::cam::Node* node_camera, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void cam_parameter();
  void cam_info();
  void cam_definedPosition();

private:
  Panel* gui_render_panel;
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;

  int item_width;
  bool* show_window;
  string name;
};

}
