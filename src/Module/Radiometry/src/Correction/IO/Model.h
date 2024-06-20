#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Model;}
namespace rad::correction::io{class Measure;}


namespace rad::correction::io{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::correction::Node* node_correction);
  ~Model();

public:
  //Main function
  void import_model();
  void export_model();

  //Subfunction
  void write_device_info();
  void write_depth_mode_model();
  void read_device_info();
  void read_depth_mode_model();
  std::string get_current_path();

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Model* rad_model;
  rad::correction::io::Measure* rad_io_measure;
};

}
