#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf::dynamic{

//Constructor / Destructor
Manager::Manager(prf::Node* node_profiler){
  //---------------------------

  this->prf_struct = node_profiler->get_prf_struct();

  //Main profiler
  prf_struct->dynamic.profiler_main = prf::dynamic::Profiler("Main");
  prf_struct->dynamic.profiler_main.fetch_tasker("cpu");
  prf_struct->dynamic.profiler_main.fetch_tasker("gpu");
  this->add_profiler(&prf_struct->dynamic.profiler_main);

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::add_profiler(prf::dynamic::Profiler* profiler){
  //---------------------------

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

//Subfunction
void Manager::loop(int max_fps){
  //---------------------------

  prf::dynamic::Tasker* tasker_cpu = prf_struct->dynamic.profiler_main.fetch_tasker("cpu");
  prf::dynamic::Tasker* tasker_gpu = prf_struct->dynamic.profiler_main.fetch_tasker("gpu");

  tasker_cpu->loop_end();
  tasker_cpu->loop_begin(max_fps);

  tasker_gpu->loop_end();
  tasker_gpu->loop_begin();

  //---------------------------
}

}
