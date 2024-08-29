#include "Pool.h"

#include <Thread/Namespace.h>


namespace thr::routine{

//Constructor / Destructor
Pool::Pool(){
  //---------------------------

  //---------------------------
}
Pool::~Pool(){
  //---------------------------

  this->wait();

  //---------------------------
}

//Main function
void Pool::run(){
  //---------------------------

  std::lock_guard<std::mutex> lock(mutex);
  for(auto& task : tasks){
    task->start_task();
  }

  //---------------------------
}
void Pool::wait(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  for(auto& task : tasks){
    task->wait_task();
  }

  //---------------------------
}

//Subfunction
void Pool::add_task(std::unique_ptr<thr::Routine> task){
  //---------------------------

  std::lock_guard<std::mutex> lock(mutex);
  tasks.push_back(std::move(task));

  //---------------------------
}
bool Pool::remove_task(thr::Routine* task){
  //---------------------------

  std::lock_guard<std::mutex> lock(mutex);
  auto it = std::remove_if(tasks.begin(), tasks.end(), [task](const std::unique_ptr<thr::Routine>& t){ return t.get() == task; });
  if(it != tasks.end()){
    (*it)->stop_task();
    tasks.erase(it, tasks.end());
    return true;
  }

  //---------------------------
  return false;
}

}
