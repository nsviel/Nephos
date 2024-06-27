#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  //Main profiler
  this->profiler_main = new prf::graph::Profiler("Main");
  profiler_main->fetch_tasker("cpu");
  profiler_main->fetch_tasker("gpu");
  this->add_profiler(profiler_main);

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::add_profiler(prf::dynamic::Profiler* profiler){
  //---------------------------

  this->list_profiler.push_back(profiler);

  //---------------------------
}
void Manager::remove_profiler(prf::dynamic::Profiler* profiler){
  //---------------------------

  profiler->clean();
  this->list_profiler.remove(profiler);
  delete profiler;

  //---------------------------
}

//Subfunction
void Manager::loop_begin(int max_fps){
  //---------------------------

  prf::graph::Tasker* tasker_cpu = profiler_main->fetch_tasker("cpu");
  prf::graph::Tasker* tasker_gpu = profiler_main->fetch_tasker("gpu");

  tasker_cpu->loop_begin(max_fps);
  tasker_gpu->loop_begin();

  //---------------------------
}
void Manager::loop_end(){
  //---------------------------

  prf::graph::Tasker* tasker_cpu = profiler_main->fetch_tasker("cpu");
  prf::graph::Tasker* tasker_gpu = profiler_main->fetch_tasker("gpu");

  tasker_cpu->loop_end();
  tasker_gpu->loop_end();

  //---------------------------
}

}
