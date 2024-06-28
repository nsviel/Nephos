#include "Tasker.h"

#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::dynamic{

//Constructor / Destructor
Tasker::Tasker(std::string name){
  //---------------------------

  this->name = name;
  this->fps_control = new utl::timer::fps::Control(120);
  this->fps_counter = new utl::timer::fps::Counter();

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
void Tasker::loop(int fps){
  //---------------------------

  //Control fps and measure sleep time
  if(is_fps_control){
    this->task_begin("sleep");
    fps_control->stop_loop();
    this->task_end("sleep", -1, glm::vec4(50, 50, 50, 255));
  }

  //Init loop task
  this->reference = timer.get_time();
  this->thread_ID = utl::thread::get_ID_str();

  //FPS control
  this->is_fps_control = (fps != -1) ? true : false;
  if(is_fps_control){
    fps_control->set_fps_max(fps);
    fps_control->start_loop();
  }

  //Get loop fps count
  this->fps = fps_counter->update();

  //Update disposal task vector by this loop task vector
  this->vec_task = vec_task_current;
  this->vec_task_current.clear();


  //---------------------------
}
void Tasker::update(){
  //---------------------------

  this->plot.reset();

  //Assign tasks
  for(int i=0; i<vec_task.size(); i++){
    prf::dynamic::Task& task = vec_task[i];
    this->plot.add_task(task.ts_begin, task.ts_end, task.name, task.color);
  }

  this->plot.update();

  //---------------------------
}

//Task function
void Tasker::task_begin(std::string name, float time){
  //---------------------------

  //Check if task already exists
  prf::dynamic::Task* exist = find_task(name);
  if(exist != nullptr){
    std::cout << "[error] task already started [" << name << "]" << std::endl;
    return;
  }

  //Start timestamp
  double ts = time;
  if(ts == -1){
    ts = timer.duration_s(this->reference, timer.get_time());
  }

  //Insert task in vector
  prf::dynamic::Task task;
  task.ts_begin = ts;
  task.ts_end = 0;
  task.name = name;
  this->vec_task_current.push_back(task);

  //---------------------------
}
void Tasker::task_end(const std::string& name, float time, glm::vec4 color){
  //---------------------------

  //Search for corresponding task
  prf::dynamic::Task* task = find_task(name);
  if(task == nullptr){
    std::cout << "[error] task not started" << std::endl;
    return;
  }

  //Apply task stuff
  if(time == -1){
    utl::timer::Timepoint task_end = timer.get_time();
    task->ts_end = timer.duration_s(this->reference, task_end);
  }else{
    task->ts_end = time;
  }
  if(color != glm::vec4{0, 0, 0, 0}){
    task->color = color;
  }

  //---------------------------
}

//Subfunction
prf::dynamic::Task* Tasker::find_task(const std::string& name){
  //---------------------------

  //Search for corresponding task
  for(int i=0; i<vec_task_current.size(); i++){
    prf::dynamic::Task* task = &vec_task_current[i];

    if(task->name == name){
      return task;
    }
  }

  //---------------------------
  return nullptr;
}

}
