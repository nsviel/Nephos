#pragma once

#include <memory>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace dat::gph{class Graph;}
namespace dat::elm{class Set;}


namespace k4n::capture{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration(k4n::Node* node_k4n);
  ~Configuration();

public:
  //Main function
  void manage_configuration();
  void make_default_configuration();
  void find_calibration(std::shared_ptr<k4n::base::Sensor> sensor);
  void find_versioning(std::shared_ptr<k4n::base::Sensor> sensor);
  void make_sensor_configuration(std::shared_ptr<k4n::base::Sensor> sensor);
  void make_sensor_color_configuration(std::shared_ptr<k4n::base::Sensor> sensor);

private:
  k4n::Structure* k4n_struct;
  dat::gph::Graph* dat_graph;
  dat::elm::Set* dat_set;
};


}
