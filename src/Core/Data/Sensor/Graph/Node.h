#pragma once

#include <functional>
#include <future>
#include <string>
#include <list>

namespace dat::base{class Sensor;}


namespace dat::sensor{

struct Node{
  //---------------------------

  std::function<void(dat::base::Sensor&)> task;
  std::future<void> future;
  std::list<std::string> adjacent;              // List of dependent tasks (outgoing edges)
  std::string name = "";
  int in_degree = 0;                            // Number of incoming edges (dependencies)

  //---------------------------
};

}
