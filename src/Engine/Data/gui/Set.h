#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Data/Namespace.h>


namespace gui::rnd::data{

class Set
{
public:
  //Constructor / Destructor
  Set(bool* show_window);
  ~Set();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void set_info(utl::type::Set* set);
  void set_parameter(utl::type::Set* set);

  inline void set_selected_set(utl::type::Set* set){this->set_selected = set;}

private:
  utl::type::Set* set_selected;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
