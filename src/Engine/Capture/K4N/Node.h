#pragma once

#include <Utility/Specific/common.h>

class Engine;
namespace eng::k4n::dev{class Swarm;}
namespace eng::k4n::dev{class Connection;}


namespace eng::k4n{

class Node
{
public:
  //Constructor / Destructor
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();

  inline Engine* get_engine(){return engine;}
  inline eng::k4n::dev::Swarm* get_k4n_swarm(){return k4n_swarm;}
  //inline eng::k4n::data::Cloud* get_k4a_cloud(){return k4a_cloud;}

private:
  Engine* engine;
  eng::k4n::dev::Swarm* k4n_swarm;
  eng::k4n::dev::Connection* k4n_connection;
  //eng::k4n::data::Cloud* k4a_cloud;

  bool show_kinect;
};

}
