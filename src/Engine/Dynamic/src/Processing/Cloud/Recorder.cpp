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

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::start_thread(dyn::base::Sensor* sensor){
  if(!sensor->state.record) return;
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Recorder::run_thread(dyn::base::Sensor* sensor){
  //---------------------------

  if(sensor->vec_recorder.size() == 1){
    sensor->vec_recorder[0]->record_sensor(sensor, sensor->data.path.data);
  }else{
    for(int i=0; i<sensor->vec_recorder.size(); i++){
      dyn::base::Recorder* recorder = sensor->vec_recorder[i];

      if(recorder->format == sensor->data.format){
        recorder->record_sensor(sensor, sensor->data.path.data);
      }
    }
  }

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

}
