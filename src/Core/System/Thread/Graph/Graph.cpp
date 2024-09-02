#include "Graph.h"

#include <Thread/Namespace.h>
#include <Utility/Namespace.h>
#include <vector>
#include <queue>


namespace thr::gph{

// Constructor / Destructor
Graph::Graph(){
  //---------------------------



  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::add_task(const std::string& task_name, std::function<void(dat::base::Entity&)> func) {
  //---------------------------
/*
  std::unique_lock<std::mutex> lock(mutex);
  map_node[task_name].task = std::move(func);
*/
  //---------------------------
}
void Graph::add_dependency(const std::string& A, const std::string& B){
  //---------------------------
/*
  std::unique_lock<std::mutex> lock(mutex);
  map_node[A].adjacent.push_back(B);
  map_node[B].in_degree++;
*/
  //---------------------------
}
void Graph::execute(thr::gph::Pool& thread_pool, dat::base::Entity& entity){
  //---------------------------
/*
  std::queue<std::string> in_degree_0;

  // Initialize the queue with tasks having zero in-degree
  {
    std::unique_lock<std::mutex> lock(mutex);
    for(auto& [task_name, node] : map_node){
      if(node.in_degree == 0){
        in_degree_0.push(task_name);
      }
    }
  }

  // Execute tasks
  while(!in_degree_0.empty()){
    std::string task_name = in_degree_0.front();
    in_degree_0.pop();

    // Submit the task to the thread pool
    thread_pool.submit([this, task_name, &in_degree_0](){
      map_node[task_name].task(entity);  // Execute the task

      std::unique_lock<std::mutex> lock(mutex);
      for (const std::string& dependent_task : map_node[task_name].adjacent) {
        if (--map_node[dependent_task].in_degree == 0) {
          in_degree_0.push(dependent_task);
        }
      }
    });
  }
*/
  //---------------------------
}

}
