#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  this->tasker_cpu = new prf::Tasker();
  this->tasker_gpu = new prf::Tasker();
  this->tasker_cap = new prf::Tasker();
  
  this->gpu_dev = "";

  //---------------------------
}
Manager::~Manager(){}

//Main function


}
