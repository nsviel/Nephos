#pragma once

#include <memory>

namespace dat::elm{class Node;}
namespace dat::base{class Sensor;}
namespace prf::monitor{class Manager;}
namespace utl::base{class Element;}


namespace dat::elm{

class Sensor
{
public:
  //Constructor / Destructor
  Sensor(dat::elm::Node* node_element);
  ~Sensor();

public:
  //Main function
  void init_sensor(dat::base::Sensor& sensor);
  void remove_sensor(dat::base::Sensor& sensor);
  bool is_dynamic(std::shared_ptr<utl::base::Element> element);

private:
  prf::monitor::Manager* prf_monitor;
};

}
