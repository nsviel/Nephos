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
void Profiler::clear(){
  //---------------------------

  for(int i=0; i<vec_tasker.size(); i++){
    prf::Tasker* tasker = vec_tasker[i];
    tasker->clear();
  }

  //---------------------------
}

//Tasker function
prf::Tasker* Profiler::new_tasker(string name){
  //---------------------------

  prf::Tasker* tasker = new prf::Tasker(name);
  this->vec_tasker.push_back(tasker);

  //---------------------------
  return tasker;
}
void Profiler::new_tasker(prf::Tasker* tasker){
  //---------------------------

  this->vec_tasker.push_back(tasker);

  //---------------------------
}
prf::Tasker* Profiler::get_tasker(string name){
  //---------------------------

  for(int i=0; i<vec_tasker.size(); i++){
    prf::Tasker* tasker = vec_tasker[i];
    if(tasker->get_name() == name){
      return tasker;
    }
  }

  cout<<"[error] tasker with name "<<name<<" doesn't exists"<<endl;

  //---------------------------
  return nullptr;
}
prf::vulkan::Profiler* Profiler::get_prf_vulkan(){
  //---------------------------

  for(int i=0; i<vec_tasker.size(); i++){
    prf::Tasker* tasker = vec_tasker[i];

    if(prf::vulkan::Profiler* vulkan = dynamic_cast<prf::vulkan::Profiler*>(tasker)){
      return vulkan;
    }
  }

  cout<<"[error] tasker vulkan doesn't exists"<<endl;

  //---------------------------
  return nullptr;
}

void Profiler::remove_tasker(prf::Tasker* tasker){
  //---------------------------


  //---------------------------
}

}
