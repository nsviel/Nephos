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
  this->run_task();
  
  //---------------------------
}


}
