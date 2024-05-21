#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}


namespace rad::model{

class Plot
{
public:
  //Constructor / Destructor
  Plot(rad::Node* node_radio);
  ~Plot();

public:
  //Main function
  void init();
  void plot_measure();
  void plot_model();

  //Subfunction
  void update_plot_data();
  void clear_plot_data();

private:
  rad::Structure* rad_struct;
};

}
