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
  this->run_thread();

  //---------------------------
}

}
