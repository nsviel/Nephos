#include "Tasker.h"

#include <Profiler/Namespace.h>


namespace prf::graph{

//Constructor / Destructor
Tasker::Tasker(std::string name){
  //---------------------------

  this->name = name;
  this->fps_control = new prf::fps::Control(120);
  this->fps_counter = new prf::fps::Counter();

  //---------------------------
}
Tasker::~Tasker(){
  //---------------------------

  delete fps_control;
  delete fps_counter;

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
void Tasker::loop_begin(int fps){
  //---------------------------

  //Init loop task
  this->reference = timer.get_time();
  this->name = utl::thread::get_ID_str();

  //FPS control
  this->is_fps_control = (fps != -1) ? true : false;
  if(is_fps_control){
    fps_control->set_fps_max(fps);
    fps_control->start_loop();
  }

  //---------------------------
}
void Tasker::loop_end(){
  //---------------------------

  //Control fps and measure sleep time
  if(is_fps_control){
    this->task_begin("sleep");
    fps_control->stop_loop();
    this->task_end("sleep", -1, vec4(50, 50, 50, 255));
  }

  //Get loop fps count
  this->fps = fps_counter->update();

  //Update disposal task vector by this loop task vector
  this->vec_task = vec_task_current;
  this->vec_task_current.clear();

  //---------------------------
}

//Task function
void Tasker::task_begin(std::string name){
  //---------------------------

  //Check if tasj already exists
  if(vec_task_current.size() != 0){
    for(int i=0; i<vec_task_current.size(); i++){
      prf::graph::structure::Task& task = vec_task_current[i];

      if(task.name == name){
        //cout<<"[error] task already exists -> "<<name<<endl;
        return;
      }
    }
  }

  //Insert task in vector
  prf::timer::Timepoint task_beg = timer.get_time();
  double A = timer.duration_s(this->reference, task_beg);

  prf::graph::structure::Task task;
  task.ts_begin = A;
  task.ts_end = 0;
  task.name = name;
  this->vec_task_current.push_back(task);

  //---------------------------
}
void Tasker::task_begin(std::string name, float time){
  //---------------------------

  //Check if tasj already exists
  if(vec_task_current.size() != 0){
    for(int i=0; i<vec_task_current.size(); i++){
      prf::graph::structure::Task& task = vec_task_current[i];

      if(task.name == name){
        //cout<<"[error] task already exists -> "<<name<<endl;
        return;
      }
    }
  }

  //Insert task in vector
  prf::graph::structure::Task task;
  task.ts_begin = time;
  task.ts_end = 0;
  task.name = name;
  this->vec_task_current.push_back(task);

  //---------------------------
}
void Tasker::task_follow_begin(std::string name){
  //---------------------------

  float ts_begin = 0;
  int index = vec_task_current.size() - 1;
  if(index >= 0){
    prf::graph::structure::Task& previous_task = vec_task_current[index];
    ts_begin = previous_task.ts_end;
  }

  //Insert task in vector
  prf::graph::structure::Task task;
  task.ts_begin = ts_begin;
  task.ts_end = 0;
  task.name = name;
  this->vec_task_current.push_back(task);

  //---------------------------
}
void Tasker::task_follow_end(std::string name, float time){
  //---------------------------

  for(int i=0; i<vec_task_current.size(); i++){
    prf::graph::structure::Task& task = vec_task_current[i];

    if(task.name == name){
      task.ts_end = task.ts_begin + time;
      return;
    }
  }

  //---------------------------
}
void Tasker::task_end(const std::string& name, float time, vec4 color){
  //---------------------------

  for(auto& task : vec_task_current){
    if(task.name == name){
      if(time == -1){
        prf::timer::Timepoint task_end = timer.get_time();
        task.ts_end = timer.duration_s(this->reference, task_end);
      }else{
        task.ts_end = time;
      }
      if(color != vec4{0, 0, 0, 0}){
        task.color = color;
      }
      return;
    }
  }

  std::cout << "[error] task not started" << std::endl;

  //---------------------------
}

}
