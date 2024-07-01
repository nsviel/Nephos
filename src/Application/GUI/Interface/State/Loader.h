#pragma once

#include <Utility/Base/Type/Path.h>
#include <string>

namespace gui::state{class Structure;}
namespace utl::base{class Path;}


namespace gui::state{

class Loader
{
public:
  //Constructor / Destructor
  Loader(gui::state::Structure* gui_struct);
  ~Loader();

public:
  //Main function
  void load_state(std::string path);

  //Subfunction
  void open_json(nlohmann::json& j);
  void extract_ini_settings(nlohmann::json& j);

private:
  gui::state::Structure* gui_struct;
};

}
