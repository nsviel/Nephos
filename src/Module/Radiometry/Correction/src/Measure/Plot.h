#pragma once

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Model;}
namespace dat::base{class Sensor;}


namespace rad::cor{

class Plot
{
public:
  //Constructor / Destructor
  Plot(rad::cor::Node* node_correction);
  ~Plot();

public:
  //Main function
  void init();

  //Subfunction
  void plot_measure();
  void update_plot_data(dat::base::Sensor* sensor);
  void reset_plot_data();

private:
  rad::cor::Structure* rad_struct;
  rad::cor::Model* rad_model;
};

}
