#pragma once

#include <Utility/Base/Class/Node.h>

namespace rad{class Node;}

namespace rad::cor{class Structure;}
namespace rad::cor{class Process;}
namespace rad::cor{class Measure;}
namespace rad::cor{class Model;}
namespace rad::cor{class Plot;}
namespace rad::cor{class Correction;}
namespace rad::cor::io{class Model;}
namespace rad::cor::io{class Measure;}


namespace rad::cor{

class Node : public utl::base::Node
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

  inline rad::cor::Structure* get_rad_struct(){return rad_struct;}
  inline rad::cor::Process* get_rad_process(){return rad_process;}
  inline rad::cor::Model* get_rad_model(){return rad_model;}
  inline rad::cor::Measure* get_rad_measure(){return rad_measure;}
  inline rad::cor::Plot* get_rad_plot(){return rad_plot;}
  inline rad::cor::Correction* get_rad_correction(){return rad_correction;}
  inline rad::cor::io::Model* get_rad_io_model(){return rad_io_model;}
  inline rad::cor::io::Measure* get_rad_io_measure(){return rad_io_measure;}

private:
  rad::Node* node_radio;

  rad::cor::Structure* rad_struct;
  rad::cor::Process* rad_process;
  rad::cor::Measure* rad_measure;
  rad::cor::Model* rad_model;
  rad::cor::Plot* rad_plot;
  rad::cor::Correction* rad_correction;
  rad::cor::io::Model* rad_io_model;
  rad::cor::io::Measure* rad_io_measure;
};

}
