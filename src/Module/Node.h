#pragma once

#include <Utility/Base/Class/Node.h>

namespace app{class Node;}
namespace rad{class Node;}
namespace eng{class Node;}
namespace k4n{class Node;}
namespace D455{class Node;}


namespace mod{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}

private:
  eng::Node* node_engine;
  k4n::Node* node_kinect;
  D455::Node* node_D455;
  rad::Node* node_radio;
};

}
