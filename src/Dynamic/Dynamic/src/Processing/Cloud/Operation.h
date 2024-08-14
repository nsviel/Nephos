#pragma once

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::cloud{class Recorder;}
namespace dyn::cloud{class Normal;}
namespace dyn::cloud{class Radiometry;}
namespace ope::attribut{class Color;}
namespace dyn::base{class Sensor;}
namespace dat::elm{class Entity;}


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
  ope::attribut::Color* ope_color;
  dyn::cloud::Normal* dyn_normal;
  dyn::cloud::Radiometry* dyn_radio;
  dat::elm::Entity* dat_entity;
};

}
