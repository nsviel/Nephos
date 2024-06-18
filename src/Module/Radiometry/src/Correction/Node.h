#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Process;}
namespace rad::correction{class Measure;}
namespace rad::correction{class Model;}
namespace rad::correction{class Plot;}
namespace rad::correction{class Correction;}
namespace rad::correction::io{class Model;}
namespace rad::correction::io{class Measure;}


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
  inline rad::correction::Measure* get_rad_measure(){return rad_measure;}
  inline rad::correction::Plot* get_rad_plot(){return rad_plot;}
  inline rad::correction::Correction* get_rad_correction(){return rad_correction;}
  inline rad::correction::io::Model* get_rad_io_model(){return rad_io_model;}
  inline rad::correction::io::Measure* get_rad_io_measure(){return rad_io_measure;}

private:
  rad::Node* node_radio;
  rad::correction::Structure* rad_struct;
  rad::correction::Process* rad_process;
  rad::correction::Measure* rad_measure;
  rad::correction::Model* rad_model;
  rad::correction::Plot* rad_plot;
  rad::correction::Correction* rad_correction;
  rad::correction::io::Model* rad_io_model;
  rad::correction::io::Measure* rad_io_measure;
};

}
