#include "Tasker.h"

#include <System/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::dynamic{

//Constructor / Destructor
Tasker::Tasker(std::string name){
  //---------------------------

  this->name = name;
  this->timer = new sys::timer::Chrono();
  this->fps_control = new sys::timer::fps::Control(120);
  this->fps_counter = new sys::timer::fps::Counter();

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

  this->vec_task_buffer.clear();
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
  this->reference = timer->get_time();
  this->thread_ID = sys::thread::get_ID_str();

  //FPS
  this->fps = fps_counter->update();
  this->is_fps_control = (fps != -1) ? true : false;
  if(is_fps_control){
    fps_control->set_fps_max(fps);
    fps_control->start_loop();
  }

  //Update current task vector by buffer one
  this->vec_task = vec_task_buffer;
  this->vec_task_buffer.clear();

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
    ts = timer->duration_s(this->reference, timer->get_time());
  }

  //Insert task in vector
  prf::dynamic::Task task;
  task.ts_begin = ts;
  task.ts_end = 0;
  task.name = name;
  this->vec_task_buffer.push_back(task);

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

  //Task time
  if(time == -1){
    sys::timer::Timepoint task_end = timer->get_time();
    task->ts_end = timer->duration_s(this->reference, task_end);
  }else{
    task->ts_end = time;
  }

  //Task color
  if(color != glm::vec4{0, 0, 0, 0}){
    task->color = color;
  }

  //Prevent from very low time tasks (< 0.01ms)
  if(task->ts_end - task->ts_begin < 0.00001){
    this->remove_task(name);
  }

  //---------------------------
}
void Tasker::add_task(const std::string& name, float ts_begin, float ts_end, glm::vec4 color){
  //---------------------------

  //Insert task in vector
  prf::dynamic::Task task;
  task.ts_begin = ts_begin;
  task.ts_end = ts_end;
  task.name = name;
  task.color = color;
  this->vec_task_buffer.push_back(task);

  //---------------------------
}
void Tasker::remove_task(const std::string& name){
  //---------------------------

  // Use std::remove_if to move matching tasks to the end of the vector
  auto it = std::remove_if(vec_task_buffer.begin(), vec_task_buffer.end(), [&name](const prf::dynamic::Task& task){return task.name == name;});

  // Erase the matching tasks from the vector
  vec_task_buffer.erase(it, vec_task_buffer.end());

  //---------------------------
}

//Subfunction
prf::dynamic::Task* Tasker::find_task(const std::string& name){
  //---------------------------

  //Search for corresponding task
  for(int i=0; i<vec_task_buffer.size(); i++){
    prf::dynamic::Task* task = &vec_task_buffer[i];

    if(task->name == name){
      return task;
    }
  }

  //---------------------------
  return nullptr;
}

}
