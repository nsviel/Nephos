#ifndef WIN_CAMERA_H
#define WIN_CAMERA_H

#include <GUI_base/BASE_panel.h>
#include <ELE_specific/common.h>

class GUI;
class RND_panel;
class Struct_camera;


class PAN_camera : public BASE_panel
{
public:
  //Constructor / Destructor
  PAN_camera(GUI* gui, bool* show_window, string name);
  ~PAN_camera();

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

#endif
