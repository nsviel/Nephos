#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  this->profiler_main = new prf::graph::Profiler("Main", "thread::main");
  profiler_main->new_tasker("cpu");
  profiler_main->new_tasker("gpu");
  this->add_profiler(profiler_main);
  this->profiler_vulkan = new prf::vulkan::Profiler("vulkan", "thread::main");
  this->add_profiler(profiler_vulkan);

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::add_profiler(prf::type::Profiler* profiler){
  //---------------------------

  this->list_profiler.push_back(profiler);

  //---------------------------
}
void Manager::remove_profiler(prf::type::Profiler* profiler){
  //---------------------------

  this->list_profiler.remove(profiler);
  delete profiler;

  //---------------------------
}

}
