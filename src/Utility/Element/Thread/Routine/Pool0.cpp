#include "Pool0.h"


namespace utl::thread {

//Constructor / Destructor
Pool0::Pool0(){
  //---------------------------

  //---------------------------
}
Pool0::~Pool0(){
  //---------------------------

  this->wait();

  //---------------------------
}

//Main function
void Pool0::run(){
  //---------------------------

  std::lock_guard<std::mutex> lock(mutex);
  for (auto& task : tasks){
    task->start_task();
  }

  //---------------------------
}
void Pool0::wait(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  for (auto& task : tasks){
    task->wait_task();
  }

  //---------------------------
}

//Subfunction
void Pool0::add_task(std::unique_ptr<utl::thread::Routine> task){
  //---------------------------

  std::lock_guard<std::mutex> lock(mutex);
  tasks.push_back(std::move(task));

  //---------------------------
}
bool Pool0::remove_task(utl::thread::Routine* task){
  //---------------------------

  std::lock_guard<std::mutex> lock(mutex);
  auto it = std::remove_if(tasks.begin(), tasks.end(), [task](const std::unique_ptr<utl::thread::Routine>& t){ return t.get() == task; });
  if(it != tasks.end()){
    (*it)->stop_task();
    tasks.erase(it, tasks.end());
    return true;
  }

  //---------------------------
  return false;
}

}
