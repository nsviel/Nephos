#include "Graph.h"

#include <Thread/Namespace.h>
#include <vector>
#include <queue>


namespace thr{

// Constructor / Destructor
Graph::Graph(){
  //---------------------------



  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::add_dependency(const std::string& task_name, const std::string& dependent_task_name){
  //---------------------------

  // Add a dependency between tasks
  std::unique_lock<std::mutex> lock(mutex);
  map_adj[task_name].push_back(dependent_task_name);
  map_in_degree[dependent_task_name]++;

  //---------------------------
}
void Graph::execute_tasks(thr::Pool& thread_pool){
  //---------------------------
/*
  std::queue<std::string> zero_in_degree;

  // Initialize the queue with tasks having zero in-degree
  {
    std::unique_lock<std::mutex> lock(mutex);
    for(auto& [task_name, degree] : map_in_degree){
      if(degree == 0){
        zero_in_degree.push(task_name);
      }
    }
  }

  // Execute tasks
  while(!zero_in_degree.empty()){
    std::string task_name = zero_in_degree.front();
    zero_in_degree.pop();

    // Submit the task to the thread pool
    thread_pool.submit([this, task_name, &zero_in_degree](){
      map_task[task_name]();  // Execute the task

      std::unique_lock<std::mutex> lock(mutex);
      for (const std::string& dependent_task : map_adj[task_name]) {
        if (--map_in_degree[dependent_task] == 0) {
          zero_in_degree.push(dependent_task);
        }
      }
    });
  }
*/
  //---------------------------
}

}
