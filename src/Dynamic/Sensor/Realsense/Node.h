#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn::sen{class Node;}
namespace dat{class Node;}
namespace core{class Node;}
namespace io{class Node;}

namespace rlx{class Structure;}
namespace rlx{class Importer;}


namespace rlx{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dyn::sen::Node* node_sensor);
  ~Node();

public:
  //Main function
  
  inline core::Node* get_node_core(){return node_core;}
  inline dat::Node* get_node_data(){return node_data;}

  inline rlx::Structure* get_rlx_struct(){return rlx_struct;}

private:
  io::Node* node_io;
  core::Node* node_core;
  dat::Node* node_data;

  rlx::Structure* rlx_struct;
  rlx::Importer* rlx_importer;
};

}
