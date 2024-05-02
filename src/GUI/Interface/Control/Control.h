#pragma once

#include <Utility/Specific/Common.h>

namespace gui{class Node;}
namespace gui{class Tab;}
namespace vk::window{class GLFW;}


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
  vk::window::GLFW* vk_window;
  gui::Tab* gui_tab;
};

}
