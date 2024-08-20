#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn::sen{class Node;}
namespace prf{class Node;}
namespace dat{class Node;}
namespace core{class Node;}
namespace io{class Node;}

namespace rlx{class Class;}


namespace rlx{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dyn::sen::Node* node_sensor);
  ~Node();

public:
  //Main function
  void config();
  void init();

  inline core::Node* get_node_core(){return node_core;}
  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline dat::Node* get_node_data(){return node_data;}

private:
  io::Node* node_io;
  core::Node* node_core;
  prf::Node* node_profiler;
  dat::Node* node_data;
  rlx::Class* rlx_class;
};

}
