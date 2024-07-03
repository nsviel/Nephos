#pragma once

#include <Utility/Base/Data/Path.h>
#include <nlohmann/json.hpp>
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
  void build_json_ini_settings(nlohmann::json& j);
  void dump_json(nlohmann::json& j, std::string path);
  
private:
  gui::state::Structure* gui_struct;
};

}
