#include "Profiler.h"

#include <Profiler/Namespace.h>


namespace prf::graph{

//Constructor / Destructor
Profiler::Profiler(string name, string type) : prf::type::Profiler(name, type){
  //---------------------------

  //---------------------------
}
Profiler::~Profiler(){
  //---------------------------

  //---------------------------
}

//Main function
void Profiler::clear(){
  //---------------------------

  for(int i=0; i<list_tasker.size(); i++){
    prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);
    tasker->clear();
  }

  //---------------------------
}

//Tasker function
prf::graph::Tasker* Profiler::new_tasker(string name){
  //---------------------------

  prf::graph::Tasker* tasker = new prf::graph::Tasker(name);
  this->list_tasker.push_back(tasker);

  //---------------------------
  return tasker;
}
void Profiler::new_tasker(prf::graph::Tasker* tasker){
  //---------------------------

  this->list_tasker.push_back(tasker);

  //---------------------------
}
prf::graph::Tasker* Profiler::get_or_create_tasker(string name){
  //---------------------------

  for(int i=0; i<list_tasker.size(); i++){
    prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);
    if(tasker->get_name() == name){
      return tasker;
    }
  }

  prf::graph::Tasker* tasker = new_tasker(name);

  //---------------------------
  return tasker;
}

void Profiler::remove_tasker(prf::graph::Tasker* tasker){
  //---------------------------

  list_tasker.remove(tasker);

  //---------------------------
}

}
