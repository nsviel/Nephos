#pragma once

namespace eng{class Node;}
namespace gui{class Node;}
namespace gui{class Tab;}


namespace gui::interface{

class Control
{
public:
  //Constructor / Destructor
  Control(gui::Node* gui);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();

  //Mouse

private:
  eng::Node* node_engine;
  gui::Tab* gui_tab;
};

}
