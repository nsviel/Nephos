#pragma once


#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Camera/Namespace.h>

class Engine;
class Panel;

namespace camera::gui{


class Panel
{
public:
  //Constructor / Destructor
  Panel(Engine* engine, bool* show_window, string name);
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
  camera::src::Control* cam_control;
  camera::src::Manager* cam_manager;

  int item_width;
  bool* show_window;
  string name;
};

}
