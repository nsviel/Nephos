#pragma once

#include <memory>

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dat::base{class Sensor;}
namespace prf::monitor{class Manager;}
namespace utl::base{class Element;}


namespace dyn::prc::element{

class Sensor
{
public:
  //Constructor / Destructor
  Sensor(dyn::prc::Node* node_processing);
  ~Sensor();

public:
  //Main function
  void init_sensor(std::shared_ptr<dat::base::Sensor> sensor);
  void remove_sensor(std::shared_ptr<dat::base::Sensor> sensor);
  bool is_dynamic(std::shared_ptr<utl::base::Element> element);

private:
  dyn::prc::Structure* dyn_struct;
  prf::monitor::Manager* prf_monitor;
};

}
