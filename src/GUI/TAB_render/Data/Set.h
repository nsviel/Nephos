#pragma once

#include <Utility/UTL_specific/common.h>

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
  void set_info(data::Set* set);
  void set_parameter(data::Set* set);

  inline void set_selected_set(data::Set* set){this->set_selected = set;}

private:
  data::Set* set_selected;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
