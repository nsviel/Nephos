#pragma once

#include <GUI_utility/Base_nsp.h>
#include <UTL_specific/common.h>

class GUI;
class Panel;
class Struct_camera;


namespace gui::rnd::engine{

class Camera : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Camera(GUI* gui, bool* show_window, string name);
  ~Camera();

  //Main function
  void design_panel();

  //Sub functions
  void cam_parameter();
  void cam_info();
  void cam_definedPosition();

private:
  Panel* gui_render_panel;
  Struct_camera* camera;

  int item_width;
};

}
