#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}


namespace ldr::exporter{

class Operation
{
public:
  //Constructor / Destructor
  Operation(ldr::Node* node_loader);
  ~Operation();

public:
  //Main functions


private:
  ldr::Structure* ldr_struct;
};

}
