#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  this->profiler_main = new_profiler("Main", "thread::main");
  profiler_main->new_tasker("cpu");
  profiler_main->new_tasker("gpu");
  this->profiler_vulkan = new prf::vulkan::Profiler("vulkan", "thread::main");
  this->new_profiler(profiler_vulkan);

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
void Manager::new_profiler(prf::Profiler* profiler){
  //---------------------------

  this->list_profiler.push_back(profiler);

  //---------------------------
}
void Manager::remove_profiler(prf::Profiler* profiler){
  //---------------------------

  this->list_profiler.remove(profiler);
  delete profiler;

  //---------------------------
}

}
