#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  this->tasker_main = new_tasker("cpu", "thread::main");

  //---------------------------
}
Manager::~Manager(){}

//Main function
prf::Tasker* Manager::new_tasker(string name, string type){
  //---------------------------

  prf::Tasker* tasker = new prf::Tasker(name, type);
  this->list_tasker.push_back(tasker);

  //---------------------------
  return tasker;
}
void Manager::remove_tasker(prf::Tasker* tasker){
  //---------------------------

  this->list_tasker.remove(tasker);
  delete tasker;

  //---------------------------
}

}
