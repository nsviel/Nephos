#pragma once

#include <Utility/Base/Class/Node.h>

namespace eng{class Node;}
namespace ope{class Structure;}


namespace ope{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function


  //Subfunction

  inline ope::Structure* get_ope_struct(){return ope_struct;}

private:
  eng::Node* node_engine;
  ope::Structure* ope_struct;
};

}
