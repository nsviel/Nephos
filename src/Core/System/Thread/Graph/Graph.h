#pragma once

#include <functional>
#include <unordered_map>
#include <mutex>
#include <string>
#include <list>

namespace thr{class Pool;}


namespace thr{

class Graph
{
public:
  // Constructor / Destructor
  Graph();
  ~Graph();

public:
  //Main function
  template<typename Func, typename... Args>
  void add_task(const std::string& task_name, Func&& func, Args&&... args){
    //---------------------------

    std::unique_lock<std::mutex> lock(mutex);
    map_task[task_name] = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

    //---------------------------
  }
  void add_dependency(const std::string& task_name, const std::string& dependent_task_name);
  void execute_tasks(thr::Pool& thread_pool);

private:
  std::unordered_map<std::string, std::function<void()>> map_task;
  std::unordered_map<std::string, std::list<std::string>> map_adj;
  std::unordered_map<std::string, int> map_in_degree;
  std::mutex mutex;
};

}
