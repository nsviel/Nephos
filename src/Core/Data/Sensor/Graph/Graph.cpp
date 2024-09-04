#include "Graph.h"

#include <Data/Base/Namespace.h>
#include <Data/Sensor/Namespace.h>
#include <Utility/Namespace.h>
#include <vector>
#include <future>


namespace dat::sensor{

// Constructor / Destructor
Graph::Graph(){
  //---------------------------



  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::clear(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  map_node.clear();

  //---------------------------
}
void Graph::add_task(const std::string& task_name, std::function<void(dat::base::Sensor&)> func) {
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  map_node[task_name].task = std::move(func);

  //---------------------------
}
void Graph::add_dependency(const std::string& A, const std::string& B){
  if(A == B) return;
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);

  // Check if the dependency B already exists in the adjacent list of A
  auto& adjacent_nodes = map_node[A].adjacent;
  if(std::find(adjacent_nodes.begin(), adjacent_nodes.end(), B) != adjacent_nodes.end()) return;

  // Add the new dependency
  adjacent_nodes.push_back(B);
  map_node[B].in_degree++;

  //---------------------------
}
void Graph::execute(dat::sensor::Pool& thread_pool, dat::base::Sensor& sensor){
  //---------------------------

  std::thread thread([this, &thread_pool, &sensor]() {
    this->process_graph(thread_pool, sensor);
  });
  thread.detach();

  //---------------------------
}

//Subfunction
void Graph::process_graph(dat::sensor::Pool& thread_pool, dat::base::Sensor& sensor) {
  std::queue<std::string> tasks_to_process;
  //---------------------------

  // Start processing tasks with zero in-degree
  {
    std::unique_lock<std::mutex> lock(mutex);
    for(auto& [task_name, node] : map_node) {
      if (node.in_degree == 0) {
        tasks_to_process.push(task_name);
      }
    }
  }

  // Process tasks
  while (!tasks_to_process.empty()) {
    std::string task_name = tasks_to_process.front();
    tasks_to_process.pop();

    // Wait for the current node's future to complete
    if (map_node[task_name].future.valid()) {
      map_node[task_name].future.wait();
    }

    map_node[task_name].future = process_node(task_name, thread_pool, sensor, tasks_to_process);
  }

  //---------------------------
}
std::future<void> Graph::process_node(const std::string& task_name, dat::sensor::Pool& thread_pool, dat::base::Sensor& sensor, std::queue<std::string>& tasks_to_process) {
  //---------------------------

  // Submit task
  auto task_future = thread_pool.submit([this, task_name, &sensor]() {
    map_node[task_name].task(sensor);  // Execute the task
  });

  // Wait for completion
  task_future.wait();

  // Process dependencies
  {
    std::unique_lock<std::mutex> lock(mutex);

    for(const std::string& dependent_task : map_node[task_name].adjacent) {
      tasks_to_process.push(dependent_task);
    }
  }

  //---------------------------
  return task_future;
}

}
