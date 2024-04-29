#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace k4n{class Node;}
namespace vld{class Node;}


namespace cap{

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

  inline k4n::Node* get_node_k4n(){return node_k4n;}

private:
  //Dependancy
  eng::Node* node_engine;
  prf::Node* node_profiler;

  //Child
  k4n::Node* node_k4n;
  vld::Node* node_velodyne;
};

}
