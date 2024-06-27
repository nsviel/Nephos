#pragma once

namespace gui{class Node;}


namespace gui::interface{

class Docking
{
public:
  //Constructor / Destructor
  Docking(gui::Node* gui);
  ~Docking();

public:
  //Main function
  void dock_main_node();
  void dock_save_state();
  void dock_load_state();

private:
};

}
