#include "Graph.h"

#include <Processing/Namespace.h>
#include <vector>
#include <queue>


namespace dyn::prc{

// Constructor / Destructor
Graph::Graph(dyn::prc::Node* node_processing){
  //---------------------------



  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::add_dependency(int task_id, int dependent_task_id){
  //---------------------------

  // Add a dependency between tasks
  std::unique_lock<std::mutex> lock(mutex);
  map_adj[task_id].push_back(dependent_task_id);
  map_in_degree[dependent_task_id]++;

  //---------------------------
}
void Graph::execute_tasks(){
  //---------------------------

  std::queue<int> zero_in_degree;

  // Initialize the queue with tasks having zero in-degree
  {
    std::unique_lock<std::mutex> lock(mutex);
    for(auto& [task_id, degree] : map_in_degree){
      if(degree == 0){
        zero_in_degree.push(task_id);
      }
    }
  }

  // Execute tasks
  while(!zero_in_degree.empty()){
    int task_id = zero_in_degree.front();
    zero_in_degree.pop();

    map_task[task_id]();  // Execute the task

    std::unique_lock<std::mutex> lock(mutex);
    for(int dependent_task : map_adj[task_id]){
      if(--map_in_degree[dependent_task] == 0){
        zero_in_degree.push(dependent_task);
      }
    }
  }

  //---------------------------
}

}
