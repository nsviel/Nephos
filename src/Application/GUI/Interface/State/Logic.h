#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>

namespace gui::state{class Structure;}
namespace utl::base{class Path;}


namespace gui::state{

class Logic
{
public:
  //Constructor / Destructor
  Logic(gui::state::Structure* gui_struct);
  ~Logic();

public:
  //Main function
  void update_list_file();
  void make_current_default();
  int get_idx_path_current();

private:
  gui::state::Structure* gui_struct;
};

}
