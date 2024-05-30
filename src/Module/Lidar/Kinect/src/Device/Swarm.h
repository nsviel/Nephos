#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}


namespace k4n::dev{

class Swarm
{
public:
  //Constructor / Destructor
  Swarm(k4n::Node* node_k4n);
  ~Swarm();

public:
  //Main function

public:
  k4n::dev::Master* master;
};

}
