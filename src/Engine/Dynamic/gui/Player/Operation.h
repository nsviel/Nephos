#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace ope{class Operation;}
namespace dat::base{class Set;}


namespace dyn::gui{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dyn::Node* node_dynamic);
  ~Operation();

  //Main function
  void player_transfo(dat::base::Set* set);

private:
  ope::Operation* ope_operation;
};

}
