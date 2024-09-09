#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn::sen{class Node;}
namespace dyn::prc{class Node;}
namespace dat{class Node;}
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

  inline dyn::prc::Node* get_node_processing(){return node_processing;}
  inline dat::Node* get_node_data(){return node_data;}
  inline io::Node* get_node_io(){return node_io;}

  inline rlx::Structure* get_rlx_struct(){return rlx_struct;}

private:
  dyn::prc::Node* node_processing;
  io::Node* node_io;
  dat::Node* node_data;

  rlx::Structure* rlx_struct;
  rlx::Importer* rlx_importer;
};

}
