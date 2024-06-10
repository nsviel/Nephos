#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::model{class Structure;}
namespace rad::model::sphere{class Model;}
namespace rad::model::sphere{class Measure;}
namespace rad::model::sphere{class Plot;}


namespace rad::model{

class Node
{
public:
  //Constructor / Destructor
  Node(rad::Node* node_radio);
  ~Node();

public:
  //Main function

  inline rad::model::Structure* get_rad_struct(){return rad_struct;}
  inline rad::model::sphere::Model* get_rad_model(){return rad_model;}
  inline rad::model::sphere::Measure* get_rad_measure(){return rad_measure;}
  inline rad::model::sphere::Plot* get_rad_plot(){return rad_plot;}

private:
  rad::model::Structure* rad_struct;
  rad::model::sphere::Model* rad_model;
  rad::model::sphere::Measure* rad_measure;
  rad::model::sphere::Plot* rad_plot;
};

}
