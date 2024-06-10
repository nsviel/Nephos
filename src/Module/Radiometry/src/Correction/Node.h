#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::correction{class Structure;}


namespace rad::correction{

class Node
{
public:
  //Constructor / Destructor
  Node(rad::Node* node_radio);
  ~Node();

public:
  //Main function

  inline rad::correction::Structure* get_rad_struct(){return rad_struct;}

private:
  rad::correction::Structure* rad_struct;
};

}
