#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Selection;}
namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::cloud{class Operation;}
namespace dyn::gui{class Colorization;}
namespace dyn::gui{class Transformation;}
namespace ope{class Operation;}
namespace ope::normal{class KNN;}
namespace dat::base{class Set;}
namespace dat::base{class Element;}


namespace dyn::gui{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dyn::Node* node_dynamic);
  ~Operation();

public:
  //Main function
  void design_operation();

  //Subfunction
  void draw_op_info(utl::base::Element* element);
  void draw_ope_normal(dat::base::Set* set);

private:
  dat::Selection* dat_selection;
  dyn::cloud::Operation* dyn_operation;
  dyn::Structure* dyn_struct;
  dyn::gui::Colorization* dyn_colorization;
  dyn::gui::Transformation* dyn_transformation;
  ope::Operation* ope_operation;
  ope::normal::KNN* ope_normal;
};

}
