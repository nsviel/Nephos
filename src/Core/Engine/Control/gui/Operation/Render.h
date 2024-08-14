#pragma once

namespace core{class Node;}
namespace ctl{class Node;}
namespace ctl{class Structure;}


namespace ctl::gui{

class Render
{
public:
  //Constructor / Destructor
  Render(ctl::Node* node_control);
  ~Render();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard();

private:
  ctl::Structure* ctl_struct;
  core::Node* node_core;
};

}
