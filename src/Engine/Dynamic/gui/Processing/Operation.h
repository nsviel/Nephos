#pragma once

namespace dat::graph{class Selection;}
namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::cloud{class Operation;}
namespace dyn::gui{class Colorization;}
namespace dyn::gui{class Transformation;}
namespace dyn::gui{class Info;}
namespace dyn::gui{class Configuration;}
namespace ope{class Operation;}
namespace ope::normal{class KNN;}
namespace utl::base{class Element;}


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
  void draw_ope_misc(utl::base::Element* element);

private:
  dat::graph::Selection* dat_selection;
  dyn::cloud::Operation* dyn_operation;
  dyn::Structure* dyn_struct;
  dyn::gui::Colorization* dyn_colorization;
  dyn::gui::Transformation* dyn_transformation;
  dyn::gui::Info* dyn_info;
  dyn::gui::Configuration* dyn_config;
  ope::Operation* ope_operation;
  ope::normal::KNN* ope_normal;
};

}
