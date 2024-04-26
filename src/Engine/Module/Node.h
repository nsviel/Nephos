#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace rnd{class Node;}


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
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

private:
  //Dependancy
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  prf::Node* node_profiler;
  rnd::Node* node_rendering;
};

}
