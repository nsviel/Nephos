#pragma once

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::cloud{class Recorder;}
namespace dyn::cloud{class Normal;}
namespace dyn::cloud{class Radiometry;}
namespace ope::color{class Routine;}
namespace dyn::base{class Sensor;}
namespace dat::element{class Entity;}


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
  ope::color::Routine* ope_colorizer;
  dyn::cloud::Normal* dyn_normal;
  dyn::cloud::Radiometry* dyn_radio;
  dat::element::Entity* dat_entity;
};

}
