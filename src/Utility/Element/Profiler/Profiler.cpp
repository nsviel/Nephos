#include "Profiler.h"

#include <Utility/Namespace.h>


namespace utl::element{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------



  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::loop_begin(){
  //---------------------------

  this->vec_task_current.clear();
  this->reference = timer.get_time();

  //---------------------------
}
void Profiler::loop_end(){
  //---------------------------

  this->vec_task = vec_task_current;

  //---------------------------
}

//Task function
void Profiler::task_begin(string name){
  //---------------------------

  //Check if tasj already exists
  if(vec_task_current.size() != 0){
    for(int i=0; i<vec_task_current.size(); i++){
      utl::type::Task& task = vec_task_current[i];

      if(task.name == name){
        cout<<"[error] task already exists -> "<<name<<endl;
        return;
      }
    }
  }

  //Insert task in vector
  utl::timer::Timepoint task_beg = timer.get_time();
  double A = timer.duration_s(reference, task_beg);
  utl::type::Task task = {A, 0, name};
  this->vec_task_current.push_back(task);

  //---------------------------
}
void Profiler::task_end(string name){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    utl::type::Task& task = vec_task_current[i];

    if(task.name == name){
      utl::timer::Timepoint task_end = timer.get_time();
      task.time_end = timer.duration_s(reference, task_end);
      return;
    }
  }

  cout<<"[error] task didn't starts"<<endl;

  //---------------------------
}

}
