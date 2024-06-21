#pragma once

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::structure{class Sensor;}
namespace dat{class Graph;}
namespace dat{class Set;}


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
  void find_calibration(k4n::structure::Sensor* sensor);
  void make_sensor_configuration(k4n::structure::Sensor* k4n_sensor);
  void make_sensor_color_configuration(k4n::structure::Sensor* sensor);
  
private:
  k4n::Structure* k4n_struct;
  dat::Graph* dat_graph;
  dat::Set* dat_set;
};


}
