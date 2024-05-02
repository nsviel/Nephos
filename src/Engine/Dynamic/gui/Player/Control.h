#pragma once

#include <Utility/Specific/Common.h>

namespace dyn::player{class Structure;}


namespace dyn::gui{

class Control
{
public:
  //Constructor / Destructor
  Control();
  ~Control();

public:
  //Main function
  void run_control(dyn::player::Structure* player);

  //Keyboard
  void control_keyboard(dyn::player::Structure* player);

private:
};

}
