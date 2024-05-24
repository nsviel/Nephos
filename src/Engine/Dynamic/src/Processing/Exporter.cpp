#include "Exporter.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Loader/Namespace.h>


namespace dyn::processing{

//Constructor / Destructor
Exporter::Exporter(dyn::Node* node_dynamic){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  ldr::Node* node_loader = node_engine->get_node_loader();

  this->ldr_exporter = node_loader->get_ldr_exporter();
  this->ply_exporter = new format::ply::Exporter();
  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::start_thread(dat::base::Entity* entity){
  //---------------------------

  this->idle = false;
  auto task_function = [this, entity](){
    this->run_thread(entity);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Exporter::run_thread(dat::base::Entity* entity){
  //---------------------------
/*
  tasker->loop_begin();

  k4n::dev::Master* master = sensor->master;
  switch(master->recorder.mode){
    case dyn::recorder::MKV:{
      tasker->task_begin("recorder::mkv");
      this->make_export_to_mkv(sensor);
      tasker->task_end("recorder::mkv");
      break;
    }
    case dyn::recorder::PLY:{
      tasker->task_begin("recorder::ply");
      this->make_export_to_ply(sensor);
      tasker->task_end("recorder::ply");
      break;
    }
  }

  if(!sensor->master->record){
    tasker->reset();
  }

  tasker->loop_end();
*/
  //---------------------------
  this->idle = true;
}
void Exporter::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Exporter::make_export_to_ply(dat::base::Entity* entity, std::string path_dir, std::string path_name){
  //---------------------------

  //Check if directory exists, if not create it
  if(!utl::directory::is_exist(path)){
    utl::directory::create(path);
  }

  //Export
  string path = path_dir + "/" + path_name + ".ply";
  ply_exporter->export_binary(entity->get_data(), entity->get_pose(), path);

  //---------------------------
}

}
