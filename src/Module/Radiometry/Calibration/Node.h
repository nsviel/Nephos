#pragma once

#include <Utility/Base/Class/Node.h>

namespace rad{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal{class Process;}


namespace rad::cal{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(rad::Node* node_radio);
  ~Node();

public:
  //Main function
  void loop();

  inline rad::Node* get_node_radio(){return node_radio;}
  inline rad::cal::Structure* get_rad_struct(){return rad_struct;}
  inline rad::cal::Process* get_rad_process(){return rad_process;}

private:
  rad::Node* node_radio;
  rad::cal::Structure* rad_struct;
  rad::cal::Process* rad_process;
};

}
