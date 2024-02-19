#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  this->tasker_cpu = new_tasker("cpu");
  this->tasker_cap = new_tasker("thread::capture");
  
  //---------------------------
}
Manager::~Manager(){}

//Main function
prf::Tasker* Manager::new_tasker(string name){
  //---------------------------

  prf::Tasker* tasker = new prf::Tasker(name);
  this->vec_tasker.push_back(tasker);

  //---------------------------
  return tasker;
}

}
