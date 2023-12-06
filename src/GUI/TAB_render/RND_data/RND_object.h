#pragma once

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class RND_panel;
class ENG_scene;


class RND_object : public BASE_panel
{
public:
  //Constructor / Destructor
  RND_object(GUI* gui, bool* show_window, string name);
  ~RND_object();

  //Main function
  void design_panel();

  //Sub functions
  void object_info(Object* object);
  void object_parameter(Object* object);

  //Primitive size
  void width_line(Object* object);
  void size_point(Object* object);

  inline void set_selected_object(Object* object){this->object_selected = object;}

private:
  RND_panel* gui_render_panel;
  ENG_scene* eng_scene;

  Object* object_selected;
  int item_width;
};
