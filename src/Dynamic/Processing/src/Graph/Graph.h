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
  Graph(dyn::prc::Node* node_processing);
  ~Graph();

public:
  //Main function
  template<typename Func, typename... Args>
  void add_task(int task_id, Func&& func, Args&&... args){
    //---------------------------

    // Add a task to the graph
    std::unique_lock<std::mutex> lock(mutex);
    map_task[task_id] = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

    //---------------------------
  }
  void add_dependency(int task_id, int dependent_task_id);
  void execute_tasks();

private:
  std::unordered_map<int, std::function<void()>> map_task;
  std::unordered_map<int, std::list<int>> map_adj;
  std::unordered_map<int, int> map_in_degree;
  std::mutex mutex;
};

}
