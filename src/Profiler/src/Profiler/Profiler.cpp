#include "Profiler.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Profiler::Profiler(string name, string type){
  //---------------------------

  this->name = name;
  this->type = type;

  //---------------------------
}
Profiler::~Profiler(){
  //---------------------------

  //---------------------------
}

//Main function
prf::Tasker* Profiler::new_tasker(string name){
  //---------------------------

  prf::Tasker* tasker = new prf::Tasker(name);
  this->vec_tasker.push_back(tasker);

  //---------------------------
  return tasker;
}
void Profiler::remove_tasker(prf::Tasker* tasker){
  //---------------------------


  //---------------------------
}

}
