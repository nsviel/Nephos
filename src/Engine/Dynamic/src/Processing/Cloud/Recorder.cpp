#include "Recorder.h"

#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Utility/Namespace.h>
#include <Loader/Namespace.h>


namespace dyn::cloud{

//Constructor / Destructor
Recorder::Recorder(dyn::Node* node_dynamic){
  //---------------------------

  eng::Node* node_engine = node_dynamic->get_node_engine();
  ldr::Node* node_loader = node_engine->get_node_loader();

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->thread_pool = node_engine->get_thread_pool();
  this->thread_idle = true;

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  this->wait_thread();
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  this->thread_idle = false;
  thread_pool->add_task(task_function);

  //---------------------------
}
void Recorder::run_thread(dyn::base::Sensor* sensor){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("ope::recording");
  //---------------------------

  tasker->loop();

  //Recording
  tasker->task_begin("recording");
  this->compute_recording(sensor);
  tasker->task_end("recording");

  //---------------------------
  this->thread_idle = true;
}
void Recorder::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Recorder::compute_recording(dyn::base::Sensor* sensor){
  std::string path = sensor->data.path.build();
  //---------------------------

  if(sensor->vec_recorder.size() == 1){
    sensor->vec_recorder[0]->record_sensor(sensor, path);
  }else{
    for(int i=0; i<sensor->vec_recorder.size(); i++){
      dyn::base::Recorder* recorder = sensor->vec_recorder[i];

      if(recorder->format == sensor->data.path.format){
        recorder->record_sensor(sensor, path);
      }
    }
  }

  //---------------------------
}

}
