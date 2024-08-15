#include "Pool.h"


namespace sys::thread::task{

//Constructor / Destructor
Pool::Pool(int nb_thread){
  //---------------------------

  this->running = true;
  for(size_t i=0; i<nb_thread; i++){
    vec_thread.emplace_back(&Pool::worker_thread, this);
  }

  //---------------------------
}
Pool::~Pool(){
  //---------------------------

  {
    std::unique_lock<std::mutex> lock(mutex);
    running = false;
  }

  // Notify all vec_thread to stop
  condition.notify_all();
  for(auto& thread : vec_thread){
    thread.join();
  }

  //---------------------------
}

//Main function
void Pool::add_task(std::function<void()> task){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  queue_task.push([task](){
    // Execute the original task
    task();
  });

  // Notify one thread to pick up the task
  condition.notify_one();

  //---------------------------
}
void Pool::add_task(std::function<void()> task, bool& done){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  queue_task.push([task, &done](){
    // Execute the original task
    task();

    // Set the taskDone flag to true when the task is done
    done = true;
  });

  // Notify one thread to pick up the task
  condition.notify_one();

  //---------------------------
}

//Subfunction
void Pool::worker_thread(){
  //---------------------------

  while(true){
    std::function<void()> task;

    {
      std::unique_lock<std::mutex> lock(mutex);
      condition.wait(lock, [&] { return !queue_task.empty() || !running; });
      if(!running) return;
      task = std::move(queue_task.front());
      queue_task.pop();
    }

    // Execute the task outside the lock
    task();
  }

  //---------------------------
}

}
