#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------

  this->tasker_main = new_tasker("cpu");

  this->profiler_main = new_profiler("Main", "thread::main");
  new_profiler("truc", "thread::truc");

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




prf::Tasker* Manager::new_tasker(string name){
  //---------------------------

  prf::Tasker* tasker = new prf::Tasker(name);
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
