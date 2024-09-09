#pragma once

#include <memory>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Model;}
namespace rad::cor{class IfR;}
namespace rad::cor{class IfIt;}
namespace rad::cor{class IfRIt;}
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
  void update(dat::base::Sensor& sensor);
  void reset();

  //Subfunction
  void plot_measure();

private:
  rad::cor::Structure* rad_struct;
  rad::cor::Model* rad_model;
  rad::cor::IfR* plot_IfR;
  rad::cor::IfIt* plot_IfIt;
  rad::cor::IfRIt* plot_IfRIt;
};

}
