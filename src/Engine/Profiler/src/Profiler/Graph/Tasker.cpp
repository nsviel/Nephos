#include "Tasker.h"

#include <Profiler/Namespace.h>


namespace prf::graph{

//Constructor / Destructor
Tasker::Tasker(string name){
  //---------------------------

  this->name = name;
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
void Tasker::reset(){
  //---------------------------

  this->vec_task_current.clear();
  this->vec_task.clear();

  //---------------------------
}

//Loop function
void Tasker::loop_begin(){
  //---------------------------

  //Init loop task
  this->vec_task_current.clear();
  this->reference = timer.get_time();
  this->is_fps_control = false;
  this->thread_ID = utl::thread::get_ID_str();

  //---------------------------
}
void Tasker::loop_begin(int fps){
  //---------------------------

  //Init loop task
  this->vec_task_current.clear();
  this->reference = timer.get_time();
  this->is_fps_control = true;
  this->thread_ID = utl::thread::get_ID_str();

  //Set fps control
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
      prf::base::Task& task = vec_task_current[i];

      if(task.name == name){
        cout<<"[error] task already exists -> "<<name<<endl;
        return;
      }
    }
  }

  //Insert task in vector
  prf::timer::Timepoint task_beg = timer.get_time();
  double A = timer.duration_s(reference, task_beg);

  prf::base::Task task;
  task.ts_begin = A;
  task.ts_end = 0;
  task.name = name;
  this->vec_task_current.push_back(task);

  //---------------------------
}
void Tasker::task_begin(string name, float time){
  //---------------------------

  //Check if tasj already exists
  if(vec_task_current.size() != 0){
    for(int i=0; i<vec_task_current.size(); i++){
      prf::base::Task& task = vec_task_current[i];

      if(task.name == name){
        cout<<"[error] task already exists -> "<<name<<endl;
        return;
      }
    }
  }

  //Insert task in vector
  prf::base::Task task;
  task.ts_begin = time;
  task.ts_end = 0;
  task.name = name;
  this->vec_task_current.push_back(task);

  //---------------------------
}
void Tasker::task_follow_begin(string name){
  //---------------------------

  float ts_begin = 0;
  int index = vec_task_current.size() - 1;
  if(index >= 0){
    prf::base::Task& previous_task = vec_task_current[index];
    ts_begin = previous_task.ts_end;
  }

  //Insert task in vector
  prf::base::Task task;
  task.ts_begin = ts_begin;
  task.ts_end = 0;
  task.name = name;
  this->vec_task_current.push_back(task);

  //---------------------------
}
void Tasker::task_follow_end(string name, float time){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    prf::base::Task& task = vec_task_current[i];

    if(task.name == name){
      task.ts_end = task.ts_begin + time;
      return;
    }
  }

  //---------------------------
}
void Tasker::task_end(string name){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    prf::base::Task& task = vec_task_current[i];

    if(task.name == name){
      prf::timer::Timepoint task_end = timer.get_time();
      task.ts_end = timer.duration_s(reference, task_end);
      return;
    }
  }

  //---------------------------
}
void Tasker::task_end(string name, float time){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    prf::base::Task& task = vec_task_current[i];

    if(task.name == name){
      task.ts_end = time;
      return;
    }
  }

  //---------------------------
}
void Tasker::task_end(string name, vec4 color){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    prf::base::Task& task = vec_task_current[i];

    if(task.name == name){
      prf::timer::Timepoint task_end = timer.get_time();
      task.ts_end = timer.duration_s(reference, task_end);
      task.color = color;
      return;
    }
  }

  cout<<"[error] task no started"<<endl;

  //---------------------------
}

}
