#pragma once

#include <memory>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Plot;}
namespace rad::cor{class Measure;}
namespace rad::cor{class Model;}
namespace dat::base{class Sensor;}


namespace rad::cor::io{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::cor::Node* node_correction);
  ~Measure();

public:
  //Main function
  void import_measure(std::shared_ptr<dat::base::Sensor> sensor);
  void export_measure(std::shared_ptr<dat::base::Sensor> sensor);
  void clear_measure(std::shared_ptr<dat::base::Sensor> sensor);

private:
  rad::cor::Structure* rad_struct;
  rad::cor::Plot* rad_plot;
  rad::cor::Measure* rad_measure;
  rad::cor::Model* rad_model;
};

}
