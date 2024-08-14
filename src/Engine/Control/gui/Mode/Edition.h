#pragma once

namespace ctl{class Node;}
namespace ctl{class Structure;}
namespace ctl::control{class Edition;}
namespace ctl::control{class Wheel;}


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
  itf::control::Edition* itf_edition;
  itf::control::Wheel* itf_wheel;
};

}
