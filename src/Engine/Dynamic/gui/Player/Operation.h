#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace ope{class Operation;}
namespace dat::base{class Set;}


namespace dyn::gui{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dyn::Node* node_dynamic);
  ~Operation();

public:
  //Main function
  void design_operation(dat::base::Set* set);

  //Subfunction
  void draw_ope_button(dat::base::Set* set);
  void draw_ope_colorization(dat::base::Set* set);
  void draw_ope_normal(dat::base::Set* set);

private:
  dyn::Structure* dyn_struct;
  ope::Operation* ope_operation;
};

}
