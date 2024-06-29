#pragma once

namespace itf{class Node;}
namespace itf{class Structure;}
namespace itf::control{class Element;}


namespace itf::gui{

class Edition
{
public:
  //Constructor / Destructor
  Edition(itf::Node* node_interface);
  ~Edition();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();
  void control_keyboard_translation();

private:
  itf::Structure* itf_struct;
  itf::control::Element* itf_element;
};

}
