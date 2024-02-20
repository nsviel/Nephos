#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  this->profiler_main = new_profiler("Main", "thread::main");
  profiler_main->new_tasker("cpu");
  profiler_main->new_tasker("gpu");

  //---------------------------
}
Manager::~Manager(){}

//Main function
prf::Profiler* Manager::new_profiler(string name, string type){
  //---------------------------

  prf::Profiler* profiler = new prf::Profiler(name, type);
  this->list_profiler.push_back(profiler);

  //---------------------------
  return profiler;
}
void Manager::remove_profiler(prf::Profiler* profiler){
  //---------------------------

  this->list_profiler.remove(profiler);
  delete profiler;

  //---------------------------
}

}
