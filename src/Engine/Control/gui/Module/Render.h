#pragma once

namespace eng{class Node;}
namespace itf{class Node;}
namespace itf{class Structure;}


namespace itf::gui{

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
