#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace sce{class Node;}
namespace rad{class Node;}
namespace cap{class Node;}


namespace eng::module{

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
  inline sce::Node* get_node_scene(){return node_scene;}
  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline cap::Node* get_node_capture(){return node_capture;}

private:
  //Dependancy
  eng::Node* node_engine;
  sce::Node* node_scene;
  prf::Node* node_profiler;
  rad::Node* node_radio;
  cap::Node* node_capture;
};

}
