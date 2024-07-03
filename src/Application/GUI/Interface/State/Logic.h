#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>

namespace gui::state{class Manager;}
namespace gui::state{class Structure;}
namespace utl::base{class Path;}


namespace gui::state{

class Logic
{
public:
  //Constructor / Destructor
  Logic(gui::state::Manager* manager);
  ~Logic();

public:
  //Main function
  void update_list_file();
  void make_current_default();
  int get_idx_path_current();

private:
  gui::state::Structure* sta_struct;
};

}
