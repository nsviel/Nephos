#pragma once

#include <Utility/Base/Type/Path.h>
#include <string>

namespace gui::state{class Structure;}
namespace utl::base{class Path;}


namespace gui::state{

class Saver
{
public:
  //Constructor / Destructor
  Saver(gui::state::Structure* gui_struct);
  ~Saver();

public:
  //Main function
  void save_state(std::string path);

  //Subfunction

private:
  gui::state::Structure* gui_struct;
};

}
