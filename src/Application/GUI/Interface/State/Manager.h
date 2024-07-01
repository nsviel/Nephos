#pragma once

#include <string>

namespace gui{class Node;}
namespace gui::state{class Saver;}
namespace gui::state{class Loader;}
namespace gui::state{class Logic;}
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

private:
  gui::state::Saver* gui_save;
  gui::state::Loader* gui_load;
  gui::state::Logic* gui_logic;
  gui::state::Structure* gui_struct;
};

}
