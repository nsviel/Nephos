#pragma once

namespace dyn{class Node;}
namespace dyn{class Structure;}


namespace dyn::gui{

class Normal
{
public:
  //Constructor / Destructor
  Normal(dyn::Node* node_dynamic);
  ~Normal();

public:
  //Main function
  void design_operation();

  //Subfunction
  void draw_parameter();

private:
  dyn::Structure* dyn_struct;
};

}
