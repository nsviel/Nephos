#pragma once

#include <Utility/Base/Class/Node.h>

namespace eng{class Node;}
namespace cam{class Node;}
namespace rnd{class Node;}
namespace ctl{class Node;}


namespace eng_{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void reset();

  inline cam::Node* get_node_camera(){return node_camera;}
  inline ctl::Node* get_node_control(){return node_control;}

private:
  cam::Node* node_camera;
  rnd::Node* node_renderer;
  ctl::Node* node_control;
};

}
