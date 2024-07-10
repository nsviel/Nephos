#include "Task.h"

#include <Dynamic/Namespace.h>


namespace dyn::thread{

//Constructor / Destructor
Task::Task(){
  //---------------------------


  //---------------------------
}
Task::~Task(){}

//Main function
void Task::start_task(dyn::base::Sensor* sensor){
  //---------------------------
say("----");
  this->sensor = sensor;
  this->wait_task();

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->run = true;

    // Thread is already running, do nothing
    if (thread.joinable()) return;
    this->thread = std::thread(&Task::loop_task, this);
  }

  cv.notify_all();
sayHello();
  //---------------------------
}


}
