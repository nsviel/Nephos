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
  //---------------------------
say("----");
  // Start processing tasks with zero in-degree
  for (auto& [task_name, node] : map_node) {
    if (node.in_degree == 0) {
      process_task(task_name, thread_pool, entity);
    }
  }
sayHello();
  //---------------------------
}

//Subfunction
void Graph::process_task(const std::string& task_name, thr::gph::Pool& thread_pool, dat::base::Entity& entity) {
  //---------------------------

  // Submit the current task to the thread pool and get a future
  auto task_future = thread_pool.submit([this, task_name, &entity]() {
    map_node[task_name].task(entity);  // Execute the task
  });

  // Wait for the task to complete
  task_future.wait();

  // Process all dependencies after the current task is complete
  {
    std::unique_lock<std::mutex> lock(mutex);

    for (const std::string& dependent_task : map_node[task_name].adjacent) {
      if (map_node[dependent_task].in_degree > 0) {
        // Decrease in-degree and process if it becomes zero
        if (--map_node[dependent_task].in_degree == 0) {
          // Submit dependent task to the thread pool
          thread_pool.submit([this, dependent_task, &entity, &thread_pool]() {
            this->process_task(dependent_task, thread_pool, entity);
          });
        }
      }
    }
  }

  //---------------------------
}

}
