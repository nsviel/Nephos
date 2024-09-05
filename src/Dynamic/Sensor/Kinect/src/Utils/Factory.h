#pragma once

#include <memory>
#include <thread>

namespace k4n{class Node;}
namespace k4n::capture{class Sensor;}
namespace dat::gph{class Graph;}
namespace dat::elm{class Set;}


namespace k4n{

class Factory
{
public:
  //Constructor / Destructor
  Factory(k4n::Node* node_k4n);
  ~Factory();

public:
  //Main function
  std::shared_ptr<k4n::capture::Sensor> create_capture_sensor(int index);
  std::shared_ptr<k4n::playback::Sensor> create_playback_sensor(utl::base::Path path);

  //Subfunction
  void insert_in_kinect_set(k4n::base::Sensor& sensor);

private:
  dat::elm::Set* dat_set;
  dat::gph::Graph* dat_graph;
};

}
