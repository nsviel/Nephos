#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Process;}
namespace rad::correction{class Measure;}
namespace rad::correction{class Model;}


namespace rad::correction{

class Node
{
public:
  //Constructor / Destructor
  Node(rad::Node* node_radio);
  ~Node();

public:
  //Main function
  void init();
  void loop();

  inline rad::Node* get_node_radio(){return node_radio;}
  inline rad::correction::Structure* get_rad_struct(){return rad_struct;}
  inline rad::correction::Process* get_rad_process(){return rad_process;}
  inline rad::correction::Model* get_rad_model(){return rad_model;}

private:
  rad::Node* node_radio;
  rad::correction::Structure* rad_struct;
  rad::correction::Process* rad_process;
  rad::correction::Measure* rad_measure;
  rad::correction::Model* rad_model;
};

}
