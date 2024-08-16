#pragma once

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dyn::prc::base{class Sensor;}
namespace prf::dynamic{class Manager;}
namespace utl::base{class Element;}


namespace dyn::prc::element{

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
  bool is_dynamic(utl::base::Element* element);

private:
  dyn::Structure* dyn_struct;
  prf::dynamic::Manager* prf_dynamic;
};

}
