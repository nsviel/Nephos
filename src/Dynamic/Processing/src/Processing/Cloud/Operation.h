#pragma once

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dyn::prc::cloud{class Recorder;}
namespace dyn::prc::cloud{class Normal;}
namespace dyn::prc::cloud{class Radiometry;}
namespace dat::atr{class Color;}
namespace dyn::prc::base{class Sensor;}
namespace dat::elm{class Entity;}


namespace dyn::prc::cloud{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dyn::prc::Node* node_dynamic);
  ~Operation();

public:
  //Main function
  void run_operation(dyn::prc::base::Sensor* sensor);
  void wait_operation();

private:
  dyn::prc::Structure* dyn_struct;
  dyn::cloud::Recorder* dyn_recorder;
  dat::atr::Color* atr_color;
  dyn::cloud::Normal* dyn_normal;
  dyn::cloud::Radiometry* dyn_radio;
  dat::elm::Entity* dat_entity;
};

}
