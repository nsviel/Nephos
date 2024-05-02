#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Player;}


namespace dyn::gui{

class Control
{
public:
  //Constructor / Destructor
  Control();
  ~Control();

public:
  //Main function
  void run_control(dyn::Player* player);

  //Keyboard
  void control_keyboard(dyn::Player* player);

private:
};

}
