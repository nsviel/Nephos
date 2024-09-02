#pragma once

#include "Node.h"

#include <functional>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <future>
#include <string>
#include <list>

namespace dat::sensor{class Pool;}
namespace dat::sensor{class Node;}
namespace dat::base{class Sensor;}


namespace dat::sensor{

class Graph
{
public:
  // Constructor / Destructor
  Graph();
  ~Graph();

public:
  //Main function
  void clear();
  void add_task(const std::string& task_name, std::function<void(dat::base::Sensor&)> func);
  void add_dependency(const std::string& A, const std::string& B);
  void execute(dat::sensor::Pool& thread_pool, dat::base::Sensor& entity);

private:
  //Subfunction
  std::future<void> process_task(const std::string& task_name, dat::sensor::Pool& thread_pool, dat::base::Sensor& entity, std::queue<std::string>& tasks_to_process) ;

private:
  std::unordered_map<std::string, dat::sensor::Node> map_node;
  std::mutex mutex;
};

}
