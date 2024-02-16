#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace velodyne{class Node;}


namespace eng::capture{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void exit();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline k4n::Node* get_node_k4n(){return node_k4n;}
  eng::scene::Node* node_scene = engine->get_node_scene();

private:
  //Dependancies
  eng::Node* node_engine;
  eng::scene::Node* node_scene;

  //Subnodes
  k4n::Node* node_k4n;
  velodyne::Node* node_velodyne;
};

}
