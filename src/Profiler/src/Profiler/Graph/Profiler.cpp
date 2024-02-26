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

  for(int i=0; i<vec_tasker.size(); i++){
    prf::graph::Tasker* tasker = vec_tasker[i];
    tasker->clear();
  }

  //---------------------------
}

//Tasker function
prf::graph::Tasker* Profiler::new_tasker(string name){
  //---------------------------

  prf::graph::Tasker* tasker = new prf::graph::Tasker(name);
  this->vec_tasker.push_back(tasker);

  //---------------------------
  return tasker;
}
void Profiler::new_tasker(prf::graph::Tasker* tasker){
  //---------------------------

  this->vec_tasker.push_back(tasker);

  //---------------------------
}
prf::graph::Tasker* Profiler::get_tasker(string name){
  //---------------------------

  for(int i=0; i<vec_tasker.size(); i++){
    prf::graph::Tasker* tasker = vec_tasker[i];
    if(tasker->get_name() == name){
      return tasker;
    }
  }

  cout<<"[error] tasker with name "<<name<<" doesn't exists"<<endl;

  //---------------------------
  return nullptr;
}

void Profiler::remove_tasker(prf::graph::Tasker* tasker){
  //---------------------------


  //---------------------------
}

}
