#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>

class GUI;


namespace gui::rnd::panel{

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
  void set_info(eng::structure::Set* set);
  void set_parameter(eng::structure::Set* set);

  inline void set_selected_set(eng::structure::Set* set){this->set_selected = set;}

private:
  eng::structure::Set* set_selected;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
