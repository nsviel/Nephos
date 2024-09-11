#pragma once

#include <memory>
#include <thread>

namespace rlx{class Node;}
namespace rlx::capture{class Sensor;}
namespace rlx::base{class Sensor;}
namespace dat::gph{class Graph;}
namespace dat::elm{class Set;}


namespace rlx{

class Factory
{
public:
  //Constructor / Destructor
  Factory(rlx::Node* node_realsense);
  ~Factory();

public:
  //Main function
  std::shared_ptr<rlx::capture::Sensor> create_capture_sensor();
  std::shared_ptr<rlx::playback::Sensor> create_playback_sensor(utl::base::Path path);

  //Subfunction
  void insert_in_set(rlx::base::Sensor& sensor);

private:
  rlx::Node* node_realsense;
  dat::elm::Set* dat_set;
  dat::gph::Graph* dat_graph;
};

}
