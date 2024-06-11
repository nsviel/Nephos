#pragma once

#include <Utility/Specific/Common.h>

namespace rad::model{class Node;}
namespace rad::model{class Structure;}
namespace rad::model::sphere{class Model;}


namespace rad::model::sphere{

class Plot
{
public:
  //Constructor / Destructor
  Plot(rad::model::Node* node_model);
  ~Plot();

public:
  //Main function
  void init();
  void plot_measure();
  void plot_model();

  //Subfunction
  void update_plot_data();
  void reset_plot_data();

private:
  rad::model::Structure* rad_struct;
  rad::model::sphere::Model* rad_model;
};

}
