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

private:
  gui::state::IO* gui_io;
  gui::state::Structure* gui_struct;
};

}
