#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>

namespace gui{class Node;}
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
  void read_ini_settings(std::string& path);
  void read_panel(std::string& path);

private:
  gui::Node* node_gui;
  gui::state::Structure* sta_struct;
};

}
