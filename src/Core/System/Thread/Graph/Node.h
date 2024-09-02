#pragma once

#include <Data/Base/Element/Entity.h>
#include <functional>
#include <string>
#include <list>


namespace thr::gph{

struct Node{
  //---------------------------

  int in_degree = 0;                            // Number of incoming edges (dependencies)
  std::list<std::string> adjacent;              // List of dependent tasks (outgoing edges)
  std::function<void(dat::base::Entity&)> task;

  //---------------------------
};

}
