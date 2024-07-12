#pragma once

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::cloud{class Recorder;}
namespace dyn::cloud{class Normal;}
namespace dyn::cloud{class Radiometry;}
namespace dyn::cloud{class Colorizer;}
namespace dyn::base{class Sensor;}


namespace dyn::cloud{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dyn::Node* node_dynamic);
  ~Operation();

public:
  //Main function
  void run_operation(dyn::base::Sensor* sensor);
  void wait_operation();

private:
  dyn::Structure* dyn_struct;
  dyn::cloud::Recorder* dyn_recorder;
  dyn::cloud::Colorizer* dyn_colorizer;
  dyn::cloud::Normal* dyn_normal;
  dyn::cloud::Radiometry* dyn_radio;
};

}
