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
void Task::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  this->sensor = sensor;
  this->wait_thread();

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->run = true;

    // Thread is already running, do nothing
    if (thread.joinable()) return;
    this->thread = std::thread(&Task::loop_thread, this);
  }

  cv.notify_all();
  is_running.set_value(true);

  //---------------------------
}


}
