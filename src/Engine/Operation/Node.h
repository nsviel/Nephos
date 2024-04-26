#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace eng::cam{class Node;}



namespace ope{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void gui();
  void control();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::cam::Node* get_node_camera(){return node_camera;}

private:
  //Dependancy
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  eng::cam::Node* node_camera;

};

}
