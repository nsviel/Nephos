#pragma once

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace prf::dynamic{class Manager;}


namespace dyn::element{

class Sensor
{
public:
  //Constructor / Destructor
  Sensor(dyn::Node* node_dynamic);
  ~Sensor();

public:
  //Main function
  void init_sensor(dyn::base::Sensor* sensor);
  void remove_sensor(dyn::base::Sensor* sensor);

private:
  dyn::Structure* dyn_struct;
  prf::dynamic::Manager* prf_dynamic;
};

}
