#pragma once

namespace rad::calibration{class Node;}
namespace rad::calibration{class Structure;}
namespace rad::calibration{class Model;}


namespace rad::calibration{

class Plot
{
public:
  //Constructor / Destructor
  Plot(rad::calibration::Node* node_calibration);
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
