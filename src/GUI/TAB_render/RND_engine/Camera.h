#pragma once

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class RND_panel;
class Struct_camera;


namespace gui::rnd::panel{

class Camera : public BASE_panel
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
  RND_panel* gui_render_panel;
  Struct_camera* camera;

  int item_width;
};

}
