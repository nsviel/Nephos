#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace eng::scene{class Node;}
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
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline prf::Node* get_node_profiler(){return node_profiler;}
  
private:
  //Dependancy
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  prf::Node* node_profiler;

  //Child
  k4n::Node* node_k4n;
  velodyne::Node* node_velodyne;
};

}
