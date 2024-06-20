#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Plot;}
namespace rad::correction{class Measure;}
namespace rad::correction{class Model;}


namespace rad::correction::io{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::correction::Node* node_correction);
  ~Measure();

public:
  //Main function
  void import_measure();
  void export_measure();
  void clear_measure();
  std::string get_current_path();
  
private:
  rad::correction::Structure* rad_struct;
  rad::correction::Plot* rad_plot;
  rad::correction::Measure* rad_measure;
  rad::correction::Model* rad_model;
};

}
