#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace itf{class Node;}
namespace itf{class Structure;}


namespace itf::control{

class Element
{
public:
  //Constructor / Destructor
  Element(itf::Node* node_interface);
  ~Element();

public:
  //Main function


private:
  itf::Structure* itf_struct;
};

}
