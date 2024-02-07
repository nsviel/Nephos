#include "Tasker.h"

#include <Utility/Namespace.h>


namespace prf{

//Constructor / Destructor
Tasker::Tasker(){
  //---------------------------



  //---------------------------
}
Tasker::~Tasker(){}

//Main function
void Tasker::clear(){
  //---------------------------

  this->vec_task_current.clear();
  this->vec_task.clear();

  //---------------------------
}

//Loop function
void Tasker::loop_begin(){
  //---------------------------

  this->vec_task_current.clear();
  this->reference = timer.get_time();

  //---------------------------
}
void Tasker::loop_end(){
  //---------------------------

  this->vec_task = vec_task_current;

  //---------------------------
}

//Task function
void Tasker::task_begin(string name){
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
void Tasker::task_end(string name){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    utl::type::Task& task = vec_task_current[i];

    if(task.name == name){
      utl::timer::Timepoint task_end = timer.get_time();
      task.time_end = timer.duration_s(reference, task_end);
      return;
    }
  }

  //---------------------------
}
void Tasker::task_end(string name, vec4 color){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    utl::type::Task& task = vec_task_current[i];

    if(task.name == name){
      utl::timer::Timepoint task_end = timer.get_time();
      task.time_end = timer.duration_s(reference, task_end);
      task.color = color;
      return;
    }
  }

  cout<<"[error] task no started"<<endl;

  //---------------------------
}

}
