#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>

namespace gui{class Node;}
namespace gui::state{class Manager;}
namespace gui::state{class Structure;}
namespace utl::base{class Path;}


namespace gui::state{

class Saver
{
public:
  //Constructor / Destructor
  Saver(gui::state::Manager* manager);
  ~Saver();

public:
  //Main function
  void save_state();

  //Subfunction
  void write_ini_settings(std::string& path);
  void write_panel(std::string& path);

private:
  gui::Node* node_gui;
  gui::state::Structure* sta_struct;
};

}
