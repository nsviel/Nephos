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
void Graph::add_task(int task_id, std::function<void()> task) {
  //---------------------------

  tasks[task_id] = task;

  //---------------------------
}

void Graph::add_dependency(int task_id, int dependent_task_id) {
  //---------------------------

  adj_list[task_id].push_back(dependent_task_id);
  in_degree[dependent_task_id]++;

  //---------------------------
}

void Graph::execute_tasks() {
  //---------------------------

  std::queue<int> zero_in_degree;
  for (auto& [task_id, degree] : in_degree) {
    if (degree == 0) {
      zero_in_degree.push(task_id);
    }
  }

  while(!zero_in_degree.empty()) {
    int task_id = zero_in_degree.front();
    zero_in_degree.pop();

    tasks[task_id]();  // Execute the task

    for (int dependent_task : adj_list[task_id]) {
      if (--in_degree[dependent_task] == 0) {
        zero_in_degree.push(dependent_task);
      }
    }
  }

  //---------------------------
}

}
