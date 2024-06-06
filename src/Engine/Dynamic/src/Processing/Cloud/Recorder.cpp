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
  if(dyn_struct->recorder.enable == false) return;
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
/*
  switch(master->recorder.mode){
    case dyn::recorder::MKV:{
      this->make_export_to_mkv(sensor);
      break;
    }
    case dyn::recorder::PLY:{
      this->make_export_to_ply(sensor);
      break;
    }
  }
*/
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
void Recorder::make_export_to_ply(dyn::base::Sensor* sensor, std::string path_dir, std::string path_name){
  //---------------------------
/*
  //Check if directory exists, if not create it
  if(!utl::directory::is_exist(path_dir)){
    utl::directory::create(path_dir);
  }

  //Export
  string path = path_dir + "/" + path_name + ".ply";
  ply_exporter->export_binary(entity->data, &entity->pose;, path);
*/
  //---------------------------
}

}
