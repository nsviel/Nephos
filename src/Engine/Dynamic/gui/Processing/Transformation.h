#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace ope{class Operation;}


namespace dyn::gui{

class Transformation
{
public:
  //Constructor / Destructor
  Transformation(dyn::Node* node_dynamic);
  ~Transformation();

public:
  //Main function
  void design_transformation();

  //Subfunction


private:
  dyn::Structure* dyn_struct;
  ope::Operation* ope_operation;
};

}
