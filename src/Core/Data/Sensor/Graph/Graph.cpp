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
void Graph::add_task(const std::string& task_name, std::function<void(dat::base::Sensor&)> func){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  map_node[task_name].name = task_name;
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

  std::thread thread([this, &thread_pool, &sensor](){
    this->process_graph(thread_pool, sensor);
  });
  thread.detach();

  //this->process_graph(thread_pool, sensor);

  //---------------------------
}

//Subfunction
void Graph::process_graph(dat::sensor::Pool& thread_pool, dat::base::Sensor& sensor){
  std::queue<std::string> queue_running;
  //---------------------------

  //Retrieve zero in-degree nodes
  {
    for(auto& [task_name, node] : map_node){
      if (node.in_degree == 0){
        queue_running.push(task_name);
      }
    }
  }

  // Process list of to-proceed nodes
  while (!queue_running.empty()){
    std::string task_name = queue_running.front();
    queue_running.pop();

    // Wait for the current node's future to complete
    /*dat::sensor::Node& node = map_node[task_name];
    if (node.future.valid()){
      node.future.wait();
    }*/

    //Start following nodes
    this->process_node(task_name, thread_pool, sensor, queue_running);
  }

  //---------------------------
}
void Graph::process_node(const std::string& task_name, dat::sensor::Pool& thread_pool, dat::base::Sensor& sensor, std::queue<std::string>& queue_running){
  //---------------------------

  // Submit task
  map_node[task_name].future = thread_pool.submit([this, task_name, &sensor](){
    map_node[task_name].task(sensor);  // Execute the task
  });

  //If no dependence break
  if(map_node[task_name].adjacent.empty()) return;

  // Wait for in degree node to complete and then run dependencies
  map_node[task_name].future.wait();

  // Process dependencies
  {
    for(const std::string& dependent_task : map_node[task_name].adjacent){
      queue_running.push(dependent_task);
    }
  }

  //---------------------------
}
void Graph::wait_completion(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);

  // Iterate over all tasks in the map and wait for their futures to complete
  for (auto& [task_name, node] : map_node){
    if (node.future.valid()){
      node.future.wait();  // Wait for the task to complete
    }
  }

  //---------------------------
}

}
