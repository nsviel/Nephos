#pragma once

namespace dyn{class Node;}
namespace dyn{class Structure;}


namespace ope::gui{

class Normal
{
public:
  //Constructor / Destructor
  Normal(dyn::Node* node_dynamic);
  ~Normal();

public:
  //Main function
  void design_normal();

  //Subfunction
  void draw_parameter();

private:
  dyn::Structure* dyn_struct;
};

}
