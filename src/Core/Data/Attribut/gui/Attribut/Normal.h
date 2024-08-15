#pragma once

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}


namespace dat::atr::gui{

class Normal
{
public:
  //Constructor / Destructor
  Normal(dat::atr::Node* node_attribut);
  ~Normal();

public:
  //Main function
  void design_normal();

  //Subfunction
  void draw_parameter();

private:
  dat::atr::Structure* atr_struct;
};

}
