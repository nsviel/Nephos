#pragma once

#include <Engine/Entity/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Scene/Namespace.h>

class GUI;


namespace gui::rnd::data{

class Set
{
public:
  //Constructor / Destructor
  Set(GUI* gui, bool* show_window);
  ~Set();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void set_info(eng::data::Set* set);
  void set_parameter(eng::data::Set* set);

  inline void set_selected_set(eng::data::Set* set){this->set_selected = set;}

private:
  eng::scene::Operation* sce_operation;

  eng::data::Set* set_selected;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
