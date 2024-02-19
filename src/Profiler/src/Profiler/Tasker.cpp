#include "Tasker.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Tasker::Tasker(string name, string type){
  //---------------------------

  this->name = name;
  this->type = type;
  this->fps_control = new prf::fps::Control(120);
  this->fps_counter = new prf::fps::Counter();
  this->gui_graph = new prf::improfil::Manager(name);
  this->is_fps_control = false;

  //---------------------------
}
Tasker::~Tasker(){
  //---------------------------

  delete fps_control;
  delete fps_counter;
  delete gui_graph;

  //---------------------------
}

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
  this->is_fps_control = false;

  //---------------------------
}
void Tasker::loop_begin(int fps){
  //---------------------------

  this->vec_task_current.clear();
  this->reference = timer.get_time();
  this->is_fps_control = true;
  fps_control->set_fps_max(fps);
  fps_control->start_loop();

  //---------------------------
}
void Tasker::loop_end(){
  //---------------------------

  //Control fps and measure sleep time
  if(is_fps_control){
    this->task_begin("sleep");
    fps_control->stop_loop();
    this->task_end("sleep", vec4(50, 50, 50, 255));
  }

  //Get loop fps
  this->loop_fps = fps_counter->update();

  //Update disposal task vector by this loop task vector
  this->vec_task = vec_task_current;

  //---------------------------
}

//Task function
void Tasker::task_begin(string name){
  //---------------------------

  //Check if tasj already exists
  if(vec_task_current.size() != 0){
    for(int i=0; i<vec_task_current.size(); i++){
      prf::type::Task& task = vec_task_current[i];

      if(task.name == name){
        cout<<"[error] task already exists -> "<<name<<endl;
        return;
      }
    }
  }

  //Insert task in vector
  prf::timer::Timepoint task_beg = timer.get_time();
  double A = timer.duration_s(reference, task_beg);
  prf::type::Task task = {A, 0, name};
  this->vec_task_current.push_back(task);

  //---------------------------
}
void Tasker::task_end(string name){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    prf::type::Task& task = vec_task_current[i];

    if(task.name == name){
      prf::timer::Timepoint task_end = timer.get_time();
      task.time_end = timer.duration_s(reference, task_end);
      return;
    }
  }

  //---------------------------
}
void Tasker::task_end(string name, vec4 color){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    prf::type::Task& task = vec_task_current[i];

    if(task.name == name){
      prf::timer::Timepoint task_end = timer.get_time();
      task.time_end = timer.duration_s(reference, task_end);
      task.color = color;
      return;
    }
  }

  cout<<"[error] task no started"<<endl;

  //---------------------------
}

}
