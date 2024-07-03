#pragma once

#include <Utility/Base/Data/Path.h>
#include <nlohmann/json.hpp>
#include <string>

namespace gui::state{class Manager;}
namespace gui::state{class Structure;}
namespace utl::base{class Path;}


namespace gui::state{

class Loader
{
public:
  //Constructor / Destructor
  Loader(gui::state::Manager* manager);
  ~Loader();

public:
  //Main function
  void load_state(std::string path);

  //Subfunction
  void open_json(nlohmann::json& j, std::string path);
  void extract_ini_settings(nlohmann::json& j);

private:
  gui::state::Structure* sta_struct;
};

}
