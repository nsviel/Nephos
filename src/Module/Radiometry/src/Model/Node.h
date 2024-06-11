#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::model{class Structure;}
namespace rad::model::sphere{class Model;}
namespace rad::model::chart{class Model;}


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
  inline rad::model::sphere::Model* get_model_sphere(){return model_sphere;}
  inline rad::model::chart::Model* get_model_chart(){return model_chart;}

private:
  rad::model::Structure* rad_struct;
  rad::model::sphere::Model* model_sphere;
  rad::model::chart::Model* model_chart;
};

}
