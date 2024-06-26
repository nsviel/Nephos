#include "Profiler.h"

#include <Profiler/Namespace.h>


namespace prf::graph{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  this->type = prf::base::GRAPH;

  //---------------------------
}
Profiler::Profiler(string name){
  //---------------------------

  this->name = name;
  this->type = prf::base::GRAPH;

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::reset(){
  //---------------------------

  for(int i=0; i<list_tasker.size(); i++){
    prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);
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

//Tasker function
prf::graph::Tasker* Profiler::fetch_tasker(std::string name){
  //---------------------------

  //Check if tasker name already exists
  for(int i=0; i<list_tasker.size(); i++){
    prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);
    if(tasker->name == name){
      return tasker;
    }
  }

  //Else create new one
  prf::graph::Tasker* tasker = new prf::graph::Tasker(name);
  this->list_tasker.push_back(tasker);

  //---------------------------
  return tasker;
}
void Profiler::insert_tasker(prf::graph::Tasker* tasker){
  //---------------------------

  //Check if tasker name already exists
  for(int i=0; i<list_tasker.size(); i++){
    prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);
    if(tasker->name == name){
      return;
    }
  }

  //Else insert it
  this->list_tasker.push_back(tasker);

  //---------------------------
}
void Profiler::remove_tasker(prf::graph::Tasker* tasker){
  //---------------------------

  list_tasker.remove(tasker);

  //---------------------------
}

}
