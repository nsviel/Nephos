#pragma once

namespace eng{class Node;}
namespace ctl{class Node;}
namespace ctl{class Structure;}


namespace ctl::gui{

class Render
{
public:
  //Constructor / Destructor
  Render(itf::Node* node_interface);
  ~Render();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard();

private:
  itf::Structure* itf_struct;
  eng::Node* node_engine;
};

}
