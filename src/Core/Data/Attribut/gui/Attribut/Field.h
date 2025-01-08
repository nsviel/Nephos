#pragma once

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}


namespace dat::atr::gui{

class Field
{
public:
  //Constructor / Destructor
  Field(dat::atr::Node* node_attribut);
  ~Field();

public:
  //Main function
  void design_field();

  //Subfunction
  void draw_parameter();

private:
  dat::atr::Structure* atr_struct;
};

}
