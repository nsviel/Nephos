#pragma once

#include <Engine/Data/Namespace.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Operation/Namespace.h>

class GUI;
class Panel;


namespace gui::rnd::data{

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
  void object_info(eng::data::Object* object);
  void object_parameter(eng::data::Object* object);

  //Primitive size
  void object_line(eng::data::Object* object);
  void object_point(eng::data::Object* object);

  inline void set_selected_object(eng::data::Object* object){this->object_selected = object;}

private:
  Panel* gui_render_panel;
  eng::ope::Attribut* attributManager;
  eng::scene::Scene* eng_scene;

  eng::data::Object* object_selected;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
