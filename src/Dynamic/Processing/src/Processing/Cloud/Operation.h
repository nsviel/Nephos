#pragma once

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dyn::prc::cloud{class Recorder;}
namespace dyn::prc::cloud{class Normal;}
namespace dyn::prc::cloud{class Radiometry;}
namespace dat::atr{class Color;}
namespace dat::base{class Sensor;}
namespace dat::elm{class Entity;}


namespace dyn::prc::cloud{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dyn::prc::Node* node_processing);
  ~Operation();

public:
  //Main function
  void run_operation(dat::base::Sensor* sensor);
  void wait_operation();

private:
  dyn::prc::Structure* dyn_struct;
  dyn::prc::cloud::Recorder* dyn_recorder;
  dat::atr::Color* atr_color;
  dyn::prc::cloud::Normal* dyn_normal;
  dyn::prc::cloud::Radiometry* dyn_radio;
  dat::elm::Entity* dat_entity;
};

}
