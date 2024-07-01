#pragma once

namespace gui{class Node;}


namespace gui::interface{

class Docking
{
public:
  //Constructor / Destructor
  Docking(gui::Node* node_gui);
  ~Docking();

public:
  //Main function
  void loop();

  //Subfunction
  void docking_space();

private:
};

}
