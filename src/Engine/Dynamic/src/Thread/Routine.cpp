#include "Routine.h"

#include <Dynamic/Namespace.h>


namespace dyn::thread{

//Constructor / Destructor
Routine::Routine(){
  //---------------------------


  //---------------------------
}
Routine::~Routine(){}

//Main function
void Routine::start_task(dyn::base::Sensor* sensor){
  //---------------------------

  this->sensor = sensor;
  this->wait_task();

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->run = true;
    cv.notify_all();

    // Thread is already running, do nothing
    if (thread.joinable()) return;
    this->thread = std::thread(&Routine::loop_task, this);
  }

  //---------------------------
}


}
