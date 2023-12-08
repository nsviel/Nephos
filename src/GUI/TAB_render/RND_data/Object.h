#pragma once

#include <GUI_utility/Base_nsp.h>
#include <UTL_specific/common.h>

class GUI;
class Panel;
class ENG_scene;


namespace gui::rnd::panel{

class Object : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Object(GUI* gui, bool* show_window, string name);
  ~Object();

  //Main function
  void design_panel();

  //Sub functions
  void object_info(data::Object* object);
  void object_parameter(data::Object* object);

  //Primitive size
  void width_line(data::Object* object);
  void size_point(data::Object* object);

  inline void set_selected_object(data::Object* object){this->object_selected = object;}

private:
  Panel* gui_render_panel;
  ENG_scene* eng_scene;

  data::Object* object_selected;
  int item_width;
};

}
