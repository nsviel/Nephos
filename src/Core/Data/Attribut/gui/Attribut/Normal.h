#pragma once

namespace ope{class Node;}
namespace ope{class Structure;}


namespace dat::atr::gui{

class Normal
{
public:
  //Constructor / Destructor
  Normal(ope::Node* node_operation);
  ~Normal();

public:
  //Main function
  void design_normal();

  //Subfunction
  void draw_parameter();

private:
  ope::Structure* ope_struct;
};

}
