#pragma once

namespace itf{class Node;}
namespace itf{class Structure;}


namespace itf::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(itf::Node* node_interface);
  ~Control();

public:
  //Main function


private:
  itf::Structure* itf_struct;
};

}
