#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace ope{class Operation;}
namespace ope::normal{class KNN;}
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
  void draw_op_info(dat::base::Set* set);
  void draw_ope_transformation(dat::base::Set* set);
  void draw_ope_colorization(dat::base::Set* set);
  void draw_ope_normal(dat::base::Set* set);
  void draw_ope_recorder(dat::base::Set* set);

private:
  dyn::Structure* dyn_struct;
  ope::Operation* ope_operation;
  ope::normal::KNN* ope_normal;
};

}
