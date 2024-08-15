#pragma once

#include <Utility/Base/Class/Node.h>

namespace dat{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr::gui{class Panel;}


namespace dat::atr{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dat::Node* node_data);
  ~Node();

public:
  //Main function


  //Subfunction

  inline core::Node* get_node_core(){return node_core;}
  inline dat::atr::Structure* get_atr_struct(){return atr_struct;}


private:
  core::Node* node_core;
  dat::atr::Structure* atr_struct;
};

}
