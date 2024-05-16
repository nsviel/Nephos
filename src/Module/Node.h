#pragma once

#include <Utility/Base/Type/Node.h>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace rad{class Node;}


namespace mod{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void clean();
  void gui();

  inline rad::Node* get_node_radio(){return node_radio;}
  inline eng::Node* get_node_engine(){return node_engine;}

private:
  eng::Node* node_engine;
  k4n::Node* node_kinect;
  rad::Node* node_radio;
};

}
