#pragma once

#include <Thread/Graph/Node.h>
#include <functional>
#include <unordered_map>
#include <mutex>
#include <string>
#include <list>

namespace thr::gph{class Pool;}
namespace thr::gph{class Node;}
namespace dat::base{class Entity;}


namespace thr::gph{

class Graph
{
public:
  // Constructor / Destructor
  Graph();
  ~Graph();

public:
  //Main function
  void add_task(const std::string& task_name, std::function<void(dat::base::Entity&)> func);
  void add_dependency(const std::string& A, const std::string& B);
  void execute(thr::gph::Pool& thread_pool, dat::base::Entity& entity);

private:
  //Subfunction
  void retrieve_all_0_in_degree(std::queue<std::string>& in_degree_0);
  void process_task(const std::string& task_name, dat::base::Entity& entity, std::queue<std::string>& in_degree_0);

private:
  std::unordered_map<std::string, thr::gph::Node> map_node;
  std::mutex mutex;
};

}
