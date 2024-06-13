#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace dat::base{class Entity;}


namespace ldr::exporter{

class Operation
{
public:
  //Constructor / Destructor
  Operation(ldr::Node* node_loader);
  ~Operation();

public:
  //Main functions
  void make_operation(dat::base::Entity* entity);

private:
  ldr::Structure* ldr_struct;
};

}
