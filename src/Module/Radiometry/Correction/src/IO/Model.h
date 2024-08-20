#pragma once

#include <string>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Measure;}
namespace rad::cor{class Model;}
namespace rad::cor::io{class Measure;}
namespace dyn::prc::base{class Sensor;}


namespace rad::cor::io{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::cor::Node* node_correction);
  ~Model();

public:
  //Main function
  void import_model(dyn::prc::base::Sensor* sensor);
  void export_model(dyn::prc::base::Sensor* sensor);

  //Subfunction
  void write_device_info(dyn::prc::base::Sensor* sensor, std::string& path);
  void write_depth_mode_model(dyn::prc::base::Sensor* sensor, std::string& path);
  void read_device_info(dyn::prc::base::Sensor* sensor, std::string& path);
  void read_depth_mode_model(dyn::prc::base::Sensor* sensor, std::string& path);

private:
  rad::cor::Structure* rad_struct;
  rad::cor::Measure* rad_measure;
  rad::cor::Model* rad_model;
  rad::cor::io::Measure* rad_io_measure;
};

}
