#pragma once

#include <functional>
#include <string>
#include <list>

namespace dat::base{class Sensor;}


namespace dat::sensor{

struct Node{
  //---------------------------

  int in_degree = 0;                            // Number of incoming edges (dependencies)
  std::list<std::string> adjacent;              // List of dependent tasks (outgoing edges)
  std::function<void(dat::base::Sensor&)> task;

  //---------------------------
};

}
