#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace ope{class Structure;}
namespace ope::gui{class Panel;}


namespace ope{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  //Main function


  //Subfunction

  inline core::Node* get_node_core(){return node_core;}


private:
  core::Node* node_core;

};

}
