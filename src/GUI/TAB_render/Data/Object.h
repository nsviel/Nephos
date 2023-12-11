#pragma once

#include <UTL_specific/common.h>

class GUI;
class Panel;
class ENG_scene;


namespace gui::rnd::panel{

class Object
{
public:
  //Constructor / Destructor
  Object(GUI* gui, bool* show_window);
  ~Object();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void object_info(eng::structure::Object* object);
  void object_parameter(eng::structure::Object* object);

  //Primitive size
  void width_line(eng::structure::Object* object);
  void size_point(eng::structure::Object* object);

  inline void set_selected_object(eng::structure::Object* object){this->object_selected = object;}

private:
  Panel* gui_render_panel;
  ENG_scene* eng_scene;

  eng::structure::Object* object_selected;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
