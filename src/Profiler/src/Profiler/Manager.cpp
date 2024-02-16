#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  this->tasker_cpu = new prf::Tasker("cpu");
  this->tasker_gpu = new prf::Tasker("gpu");
  this->tasker_cap = new prf::Tasker("thread::capture");

  this->vec_tasker.push_back(tasker_cpu);
  //this->vec_tasker.push_back(tasker_gpu);
  this->vec_tasker.push_back(tasker_cap);

  //---------------------------
}
Manager::~Manager(){}

//Main function


}
