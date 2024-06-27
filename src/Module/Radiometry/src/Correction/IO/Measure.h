#pragma once

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Plot;}
namespace rad::correction{class Measure;}
namespace rad::correction{class Model;}
namespace dyn::base{class Sensor;}


namespace rad::correction::io{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::correction::Node* node_correction);
  ~Measure();

public:
  //Main function
  void import_measure(dyn::base::Sensor* sensor);
  void export_measure(dyn::base::Sensor* sensor);
  void clear_measure(dyn::base::Sensor* sensor);

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Plot* rad_plot;
  rad::correction::Measure* rad_measure;
  rad::correction::Model* rad_model;
};

}
