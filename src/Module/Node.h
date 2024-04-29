#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace rad{class Node;}
namespace cap{class Node;}


namespace mod{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* engine);
  ~Node();

public:
  //Main function
  void config();
  void init();
  void loop();
  void gui();
  void clean();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline cap::Node* get_node_capture(){return node_capture;}

private:
  //Dependancy
  eng::Node* node_engine;
  prf::Node* node_profiler;
  rad::Node* node_radio;
  cap::Node* node_capture;
};

}
