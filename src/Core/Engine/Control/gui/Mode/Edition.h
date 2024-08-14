#pragma once

namespace ctr{class Node;}
namespace ctr{class Structure;}
namespace ctr::mode{class Edition;}
namespace ctr{class Wheel;}


namespace ctr::gui{

class Edition
{
public:
  //Constructor / Destructor
  Edition(ctr::Node* node_control);
  ~Edition();

public:
  //Main function
  void run_control();

  //Subfunction
  void control_keyboard_oneAction();
  void control_keyboard_translation();
  void control_wheel();

private:
  ctr::Structure* ctr_struct;
  ctr::mode::Edition* ctr_edition;
  ctr::Wheel* ctr_wheel;
};

}
