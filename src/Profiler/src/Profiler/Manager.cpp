#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  this->tasker_cpu = new prf::Tasker();
  this->tasker_gpu = new prf::Tasker();
  this->tasker_cap = new prf::Tasker();

  this->vec_tasker.push_back(tasker_cpu);
  this->vec_tasker.push_back(tasker_gpu);
  this->vec_tasker.push_back(tasker_cap);

  //---------------------------
}
Manager::~Manager(){}

//Main function


}
