#pragma once

#include <Utility/Specific/Common.h>

namespace dyn::base{class Player;}


namespace dyn::gui{

class Control
{
public:
  //Constructor / Destructor
  Control();
  ~Control();

public:
  //Main function
  void run_control(dyn::base::Player* player);

  //Keyboard
  void control_keyboard(dyn::base::Player* player);

private:
};

}
