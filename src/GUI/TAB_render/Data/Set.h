#pragma once

#include <GUI_utility/Base/Namespace.h>
#include <UTL_specific/common.h>

class GUI;
class Panel;


namespace gui::rnd::panel{

class Set : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Set(GUI* gui, bool* show_window, string name);
  ~Set();

  //Main function
  void design_panel();

  //Sub functions
  void set_info(data::Set* set);
  void set_parameter(data::Set* set);

  inline void set_selected_set(data::Set* set){this->set_selected = set;}

private:
  Panel* gui_render_panel;

  data::Set* set_selected;
  int item_width;
};

}
