#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::model{class Model;}
namespace rad::model{class Measure;}
namespace rad::model{class Plot;}


namespace rad::model{

class Manager
{
public:
  //Constructor / Destructor
  Manager(rad::Node* node_radio);
  ~Manager();

public:
  //Main function


  inline rad::model::Model* get_rad_model(){return rad_model;}
  inline rad::model::Measure* get_rad_measure(){return rad_measure;}
  inline rad::model::Plot* get_rad_plot(){return rad_plot;}

private:
  rad::Structure* rad_struct;
  rad::model::Model* rad_model;
  rad::model::Measure* rad_measure;
  rad::model::Plot* rad_plot;
};

}
