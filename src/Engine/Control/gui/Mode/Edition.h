#pragma once

namespace ctl{class Node;}
namespace ctl{class Structure;}
namespace ctl::mode{class Edition;}
namespace ctl{class Wheel;}


namespace ctl::gui{

class Edition
{
public:
  //Constructor / Destructor
  Edition(ctl::Node* node_control);
  ~Edition();

public:
  //Main function
  void run_control();

  //Subfunction
  void control_keyboard_oneAction();
  void control_keyboard_translation();
  void control_wheel();

private:
  itf::Structure* ctl_struct;
  ctl::mode::Edition* ctl_edition;
  ctl::Wheel* ctl_wheel;
};

}
