#pragma once

#include <Utility/Base/Type/Path.h>
#include <vector>
#include <string>

namespace gui{class Node;}
namespace gui::state{class IO;}
namespace gui::state{class Structure;}
namespace utl::base{class Path;}


namespace gui::state{

class Manager
{
public:
  //Constructor / Destructor
  Manager(gui::Node* node_gui);
  ~Manager();

public:
  //Main function
  void init();
  void loop();
  void gui();

  //Subfunction
  void load_state(std::string filename);
  void reload_state();
  void update_file_list();
  void make_current_default();
  int get_idx_path_current();

private:
  gui::state::IO* gui_io;
  gui::state::Structure* gui_struct;
};

}
