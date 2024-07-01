#pragma once

#include <Utility/Base/Type/Path.h>
#include <string>

namespace gui::state{class Structure;}
namespace utl::base{class Path;}


namespace gui::state{

class IO
{
public:
  //Constructor / Destructor
  IO(gui::state::Structure* gui_struct);
  ~IO();

public:
  //Main function
  void state_save(std::string path);
  void state_load(std::string path);

  //Subfunction
  void update_list_file();

private:
  gui::state::Structure* gui_struct;
};

}
