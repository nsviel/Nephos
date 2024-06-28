#pragma once

namespace itf{class Node;}
namespace dat::graph{class Selection;}
namespace dat::element{class Set;}
namespace itf::control{class Wheel;}
namespace ope{class Operation;}


namespace itf::gui{

class Element
{
public:
  //Constructor / Destructor
  Element(itf::Node* node_interface);
  ~Element();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();
  void control_keyboard_translation();

  //Mouse
  void control_wheel();

private:
  dat::graph::Selection* dat_selection;
  dat::element::Set* dat_set;
  ope::Operation* ope_operation;
  itf::control::Wheel* itf_wheel;
};

}
