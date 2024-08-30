#pragma once

#include <functional>
#include <unordered_map>
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
  void add_task(int task_id, std::function<void()> task);
  void add_dependency(int task_id, int dependent_task_id);
  void execute_tasks();

private:
  std::unordered_map<int, std::function<void()>> tasks;
  std::unordered_map<int, std::list<int>> adj_list;
  std::unordered_map<int, int> in_degree;
};

}
