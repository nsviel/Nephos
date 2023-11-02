#ifndef WIN_CAMERA_H
#define WIN_CAMERA_H

#include <Base/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class GUI_render_panel;
class Struct_camera;


class GUI_camera : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_camera(GUI* gui, bool* show_window, string name);
  ~GUI_camera();

  //Main function
  void design_panel();

  //Sub functions
  void cam_parameter();
  void cam_info();
  void cam_definedPosition();

private:
  GUI_render_panel* gui_render_panel;
  Struct_camera* camera;

  int item_width;
};

#endif
