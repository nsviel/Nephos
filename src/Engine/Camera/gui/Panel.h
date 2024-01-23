#pragma once


#include <Utility/Base/GUI/Panel.h>
#include <Utility/Specific/common.h>
#include <Engine/Camera/Namespace.h>

class Engine;
class Panel;

namespace eng::cam::gui{


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
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;

  int item_width;
  bool* show_window;
  string name;
};

}
