#pragma once

namespace itf{class Node;}
namespace itf{class Structure;}
namespace itf::control{class Wheel;}


namespace itf::gui{

class Wheel
{
public:
  //Constructor / Destructor
  Wheel(itf::Node* node_interface);
  ~Wheel();

public:
  //Main function
  void run_control();

  //Subfunction
  void control_wheel();

private:
  itf::Structure* itf_struct;
  itf::control::Wheel* itf_wheel;
};

}
