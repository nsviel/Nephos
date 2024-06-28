#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf::dynamic{

//Constructor / Destructor
Manager::Manager(prf::Node* node_profiler){
  //---------------------------

  this->prf_struct = node_profiler->get_prf_struct();



  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  this->add_profiler(&prf_struct->dynamic.profiler_main, "Main");

  //---------------------------
}
void Manager::loop(int max_fps){
  //---------------------------

  //CPU tasker
  prf::dynamic::Tasker* tasker_cpu = prf_struct->dynamic.profiler_main.fetch_tasker("cpu");
  tasker_cpu->loop(max_fps);

  //GPU tasker
  prf::dynamic::Tasker* tasker_gpu = prf_struct->dynamic.profiler_main.fetch_tasker("gpu");
  tasker_gpu->loop();

  //---------------------------
}

//Subfunction
void Manager::add_profiler(prf::dynamic::Profiler* profiler, std::string name){
  //---------------------------

  profiler->name = name;
  prf_struct->dynamic.list_profiler.push_back(profiler);

  //---------------------------
}
void Manager::remove_profiler(prf::dynamic::Profiler* profiler){
  //---------------------------

  profiler->clean();
  prf_struct->dynamic.list_profiler.remove(profiler);
  delete profiler;

  //---------------------------
}
prf::dynamic::Tasker* Manager::get_tasker_cpu(){
  //---------------------------

  return prf_struct->dynamic.profiler_main.fetch_tasker("cpu");

  //---------------------------
}
prf::dynamic::Tasker* Manager::get_tasker_gpu(){
  //---------------------------

  return prf_struct->dynamic.profiler_main.fetch_tasker("gpu");

  //---------------------------
}

}
