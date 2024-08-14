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
  Edition(itf::Node* node_interface);
  ~Edition();

public:
  //Main function
  void run_control();

  //Subfunction
  void control_keyboard_oneAction();
  void control_keyboard_translation();
  void control_wheel();

private:
  itf::Structure* itf_struct;
  ctl::mode::Edition* itf_edition;
  ctl::Wheel* itf_wheel;
};

}
