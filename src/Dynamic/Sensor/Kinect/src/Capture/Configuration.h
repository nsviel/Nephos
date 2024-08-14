#pragma once

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace dat::graph{class Graph;}
namespace dat::element{class Set;}


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
  void find_calibration(k4n::base::Sensor* sensor);
  void find_versioning(k4n::base::Sensor* sensor);
  void make_sensor_configuration(k4n::base::Sensor* k4n_sensor);
  void make_sensor_color_configuration(k4n::base::Sensor* sensor);

private:
  k4n::Structure* k4n_struct;
  dat::graph::Graph* dat_graph;
  dat::element::Set* dat_set;
};


}
