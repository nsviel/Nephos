#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>

namespace itf::state{class Manager;}
namespace itf::state{class Structure;}
namespace utl::base{class Path;}


namespace itf::state{

class Logic
{
public:
  //Constructor / Destructor
  Logic(itf::state::Manager* manager);
  ~Logic();

public:
  //Main function
  void update_list_file();
  void make_current_default();
  int get_idx_path_current();

private:
  itf::state::Structure* sta_struct;
};

}
