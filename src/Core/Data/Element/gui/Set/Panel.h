#pragma once

#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class Set;}
namespace dat::base{class Set;}


namespace dat::gui::set{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::elm::Node* node_element, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void set_info(dat::base::Set* set);
  void set_parameter(dat::base::Set* set);

  inline void set_selected_set(dat::base::Set* set){this->set_selected = set;}

private:
  dat::elm::Set* dat_set;

  dat::base::Set* set_selected;
  std::string panel_name;
  bool* panel_show;;
  int item_width;
};

}
