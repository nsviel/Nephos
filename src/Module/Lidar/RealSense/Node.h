#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace rad{class Node;}
namespace ldr{class Node;}


namespace rsx{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void config();
  void init();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline dat::Node* get_node_data(){return node_data;}

private:
  //Dependancy
  ldr::Node* node_loader;
  eng::Node* node_engine;
  prf::Node* node_profiler;
  rad::Node* node_radio;
  dat::Node* node_data;

  //Child
};

}
