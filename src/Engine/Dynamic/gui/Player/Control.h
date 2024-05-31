#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Selection;}
namespace dyn{class Node;}
namespace dyn::base{class Player;}


namespace dyn::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(dyn::Node* node_dynamic);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard(dyn::base::Player* player);

private:
  dat::Selection* dat_selection;
};

}
