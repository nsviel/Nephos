#pragma once

#include <Utility/Specific/Common.h>

namespace dyn::gui::player{class Structure;}


namespace dyn::gui::player{

class Control
{
public:
  //Constructor / Destructor
  Control();
  ~Control();

public:
  //Main function
  void run_control(dyn::gui::player::Structure* player);

  //Keyboard
  void control_keyboard(dyn::gui::player::Structure* player);

private:
};

}
