#pragma once


#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Camera/Namespace.h>

class Engine;
class Panel;

namespace gui::engine{


class Camera
{
public:
  //Constructor / Destructor
  Camera(Engine* engine, bool* show_window, string name);
  ~Camera();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void cam_parameter();
  void cam_info();
  void cam_definedPosition();

private:
  Panel* gui_render_panel;
  eng::camera::Control* cam_control;
  eng::camera::Manager* cam_manager;

  int item_width;
  bool* show_window;
  string name;
};

}
