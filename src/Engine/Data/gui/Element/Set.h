#pragma once

#include <string>

namespace dat{class Node;}
namespace dat::element{class Set;}
namespace dat::base{class Set;}


namespace dat::gui{

class Set
{
public:
  //Constructor / Destructor
  Set(dat::Node* node_data, bool* show_window);
  ~Set();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void set_info(dat::base::Set* set);
  void set_parameter(dat::base::Set* set);

  inline void set_selected_set(dat::base::Set* set){this->set_selected = set;}

private:
  dat::element::Set* dat_set;

  dat::base::Set* set_selected;
  std::string panel_name;
  bool* panel_show;;
  int item_width;
};

}
