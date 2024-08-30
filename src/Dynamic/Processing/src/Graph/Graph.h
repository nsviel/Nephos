#pragma once

#include <functional>
#include <unordered_map>
#include <mutex>
#include <list>

namespace dyn::prc{class Node;}


namespace dyn::prc{

class Graph
{
public:
  // Constructor / Destructor
  Graph();
  ~Graph();

public:
  //Main function
  template<typename Func, typename... Args>
  void add_task(int task_id, Func&& func, Args&&... args);
  void add_dependency(int task_id, int dependent_task_id);
  void execute_tasks(dyn::prc::Pool& thread_pool);

private:
  std::unordered_map<int, std::function<void()>> map_task;
  std::unordered_map<int, std::list<int>> map_adj;
  std::unordered_map<int, int> map_in_degree;
  std::mutex mutex;
};

}
