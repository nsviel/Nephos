#pragma once

#include <Utility/Specific/Common.h>

namespace gui::player{class Structure;}


namespace gui::player{

class Control
{
public:
  //Constructor / Destructor
  Control();
  ~Control();

public:
  //Main function
  void run_control(gui::player::Structure* player);

  //Keyboard
  void control_keyboard(gui::player::Structure* player);

private:
};

}
