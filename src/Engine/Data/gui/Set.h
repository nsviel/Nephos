#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Set;}
namespace dat::base{class Set;}


namespace dat::gui{

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
  void set_info(dat::base::Set* set);
  void set_parameter(dat::base::Set* set);

  inline void set_selected_set(dat::base::Set* set){this->set_selected = set;}

private:
  dat::Set* dat_set;

  dat::base::Set* set_selected;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
