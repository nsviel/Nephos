#include "Profiler.h"

#include <Monitor/Namespace.h>


namespace prf::monitor{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------


  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::reset(){
  //---------------------------

  for(int i=0; i<list_tasker.size(); i++){
    prf::monitor::Tasker* tasker = *next(list_tasker.begin(), i);
    tasker->reset();
  }

  //---------------------------
}
void Profiler::clean(){
  //---------------------------

  for(auto tasker : list_tasker){
    delete tasker;
  }
  list_tasker.clear();

  //---------------------------
}

//Subfunction
prf::monitor::Tasker* Profiler::fetch_tasker(std::string name){
  //---------------------------

  //Check if tasker name already exists
  for(int i=0; i<list_tasker.size(); i++){
    prf::monitor::Tasker* tasker = *next(list_tasker.begin(), i);
    if(tasker->name == name){
      return tasker;
    }
  }

  //Else create new one
  prf::monitor::Tasker* tasker = new prf::monitor::Tasker(name);
  this->list_tasker.push_back(tasker);

  //---------------------------
  return tasker;
}

}