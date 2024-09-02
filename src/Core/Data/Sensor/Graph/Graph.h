#pragma once

#include "Node.h"

#include <functional>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <string>
#include <list>

namespace thr::gph{class Pool;}
namespace thr::gph{class Node;}
namespace dat::base{class Sensor;}


namespace thr::gph{

class Graph
{
public:
  // Constructor / Destructor
  Graph();
  ~Graph();

public:
  //Main function
  void add_task(const std::string& task_name, std::function<void(dat::base::Sensor&)> func);
  void add_dependency(const std::string& A, const std::string& B);
  void execute(thr::gph::Pool& thread_pool, dat::base::Sensor& entity);

private:
  //Subfunction
  void process_task(const std::string& task_name, thr::gph::Pool& thread_pool, dat::base::Sensor& entity, std::queue<std::string>& tasks_to_process) ;

private:
  std::unordered_map<std::string, thr::gph::Node> map_node;
  std::mutex mutex;
};

}
