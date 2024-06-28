#pragma once

namespace dat{class Node;}
namespace dat::graph{class Selection;}
namespace dat::element{class Set;}
namespace dat::gui{class Wheel;}
namespace ope{class Operation;}


namespace dat::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(dat::Node* node_data);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();
  void control_keyboard_translation();

  //Mouse
  void control_wheel();

  inline dat::gui::Wheel* get_gui_wheel(){return gui_wheel;}

private:
  dat::graph::Selection* dat_selection;
  dat::element::Set* dat_set;
  ope::Operation* ope_operation;
  dat::gui::Wheel* gui_wheel;
};

}
