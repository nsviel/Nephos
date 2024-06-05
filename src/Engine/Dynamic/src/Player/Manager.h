#pragma once

#include <Dynamic/src/Base/State.h>
#include <Dynamic/src/Base/Timestamp.h>
#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat{class Selection;}


namespace dyn::player{

class Manager
{
public:
  //Constructor / Destructor
  Manager(dyn::Node* node_dynamic);
  ~Manager();

  //Main function
  void manage_update();
  void manage_query(float value);
  void manage_restart();
  void manage_reset();
  void manage_configuration();
  void manage_forward();

public:
  dat::Selection* dat_selection;
};

}
