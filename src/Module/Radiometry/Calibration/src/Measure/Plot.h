#pragma once

namespace rad::cal{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal{class Model;}


namespace rad::cal{

class Plot
{
public:
  //Constructor / Destructor
  Plot(rad::cal::Node* node_calibration);
  ~Plot();

public:
  //Main function
  void init();
  void plot_measure();

  //Subfunction
  void update_plot_data();
  void reset_plot_data();

private:

};

}
