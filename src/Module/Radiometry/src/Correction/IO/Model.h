#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Measure;}
namespace rad::correction::io{class Measure;}
namespace dyn::base{class Sensor;}


namespace rad::correction::io{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::correction::Node* node_correction);
  ~Model();

public:
  //Main function
  void import_model(dyn::base::Sensor* sensor);
  void export_model(dyn::base::Sensor* sensor);

  //Subfunction
  void write_device_info(dyn::base::Sensor* sensor, std::string& path);
  void write_depth_mode_model(dyn::base::Sensor* sensor, std::string& path);
  void read_device_info(dyn::base::Sensor* sensor, std::string& path);
  void read_depth_mode_model(dyn::base::Sensor* sensor, std::string& path);

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Measure* rad_measure;
  rad::correction::io::Measure* rad_io_measure;
};

}
