#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::model{class Model;}


namespace rad::model{

class Plot
{
public:
  //Constructor / Destructor
  Plot(rad::Node* node_radio, rad::model::Model* rad_model);
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
  rad::Structure* rad_struct;
  rad::model::Model* rad_model;
};

}
