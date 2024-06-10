#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::model{class Structure;}
namespace rad::model::chart{class Model;}


namespace rad::model::chart{

class Plot
{
public:
  //Constructor / Destructor
  Plot(rad::Node* node_radio, rad::model::chart::Model* rad_model);
  ~Plot();

public:
  //Main function
  void init();
  void plot_measure();

  //Subfunction
  void update_plot_data();
  void reset_plot_data();

private:
  rad::model::Structure* rad_struct;
  rad::model::chart::Model* rad_model;
};

}
