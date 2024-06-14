#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace ope{class Operation;}
namespace dat::base{class Element;}


namespace dyn::gui{

class Transformation
{
public:
  //Constructor / Destructor
  Transformation(dyn::Node* node_dynamic);
  ~Transformation();

public:
  //Main function
  void design_transformation(utl::base::Element* element);

  //Subfunction
  void draw_operation(utl::base::Element* element);
  void draw_matrix(utl::base::Element* element);

private:
  dyn::Structure* dyn_struct;
  ope::Operation* ope_operation;
};

}
