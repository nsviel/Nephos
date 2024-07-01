#pragma once

#include <string>

namespace gui{class Node;}
namespace gui::state{class IO;}
namespace gui::state{class Structure;}


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

  void reload_state();

  void make_current_default();
  int get_idx_path_current();

private:
  gui::state::IO* gui_io;
  gui::state::Structure* gui_struct;
};

}
