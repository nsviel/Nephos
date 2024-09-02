#include "Graph.h"

#include <Thread/Namespace.h>
#include <Utility/Namespace.h>
#include <vector>


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

  std::unique_lock<std::mutex> lock(mutex);
  map_node[task_name].task = std::move(func);

  //---------------------------
}
void Graph::add_dependency(const std::string& A, const std::string& B){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  map_node[A].adjacent.push_back(B);
  map_node[B].in_degree++;

  //---------------------------
}
void Graph::execute(thr::gph::Pool& thread_pool, dat::base::Entity& entity){
  std::queue<std::string> tasks_to_process;
  //---------------------------

  // Start processing tasks with zero in-degree
  {
    std::unique_lock<std::mutex> lock(mutex);
    for (auto& [task_name, node] : map_node) {
      if (node.in_degree == 0) {
        tasks_to_process.push(task_name);
      }
    }
  }

  // Process tasks
  while (!tasks_to_process.empty()) {
    std::string task_name = tasks_to_process.front();
    tasks_to_process.pop();

    this->process_task(task_name, thread_pool, entity, tasks_to_process);
  }

  //---------------------------
}

//Subfunction
void Graph::process_task(const std::string& task_name, thr::gph::Pool& thread_pool, dat::base::Entity& entity, std::queue<std::string>& tasks_to_process) {
  //---------------------------

  // Submit the current task to the thread pool
  auto task_future = thread_pool.submit([this, task_name, &entity]() {
    try {
      map_node[task_name].task(entity);  // Execute the task
    } catch (...) {
      // Handle exceptions if necessary
    }
  });

  // Handle task completion and dependencies
  task_future.wait(); // Wait for the task to complete

  // Process dependencies
  {
    std::unique_lock<std::mutex> lock(mutex);

    for (const std::string& dependent_task : map_node[task_name].adjacent) {
      tasks_to_process.push(dependent_task);
    }
  }

  //---------------------------
}

}
