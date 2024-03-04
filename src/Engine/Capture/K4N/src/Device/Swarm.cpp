#include "Swarm.h"

#include <Engine/Namespace.h>
#include <K4N/Namespace.h>
#include <Scene/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Swarm::Swarm(k4n::structure::Struct_k4n* struct_k4n){
  //---------------------------

  eng::scene::Node* node_scene = struct_k4n->node_scene;
  prf::Node* node_profiler = struct_k4n->node_profiler;

  this->struct_k4n = struct_k4n;
  this->profiler = node_profiler->get_prf_manager();
  this->sce_database = node_scene->get_scene_database();
  this->sce_set = new eng::scene::Set();
  this->k4n_transfo = new k4n::utils::Transformation();

  //---------------------------
}
Swarm::~Swarm(){}

//Sensor function
void Swarm::create_sensor_playback(utl::file::Path path){
  if(!utl::fct::file::is_file_exist(path.data)) return;
  //---------------------------

  //Associated master
  k4n::dev::Master* master = get_or_create_master("Playback");
  int index = sce_set->compute_number_entity(master);

  //Sensor creation
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(struct_k4n);
  sensor->name = "playback_" + to_string(index);
  sensor->param.format = utl::fct::info::get_format_from_path(path.data);
  sensor->param.file_size = utl::fct::info::get_file_size(path.data);
  sensor->param.index = index;
  sensor->param.mode = k4n::mode::PLAYBACK;
  sensor->param.path = path;
  sensor->master = master;

  //Sensor initialization
  sensor->init();
  master->insert_sensor(sensor);
  sce_database->assign_UID(sensor);
  k4n_transfo->find_transformation_from_file(sensor, path.transformation);

  //---------------------------
}
void Swarm::create_sensor_capture(){
  //---------------------------

  //Associated master
  k4n::dev::Master* master = get_or_create_master("Capture");
  int index = sce_set->compute_number_entity(master);

  //Sensor creation
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(struct_k4n);
  sensor->name = "capture_" + to_string(index);
  sensor->param.index = index;
  sensor->param.mode = k4n::mode::CAPTURE;
  sensor->master = master;

  //Sensor initialization
  sensor->init();
  master->insert_sensor(sensor);
  sce_database->assign_UID(sensor);
  sensor->run_capture();

  //---------------------------
}

//Master function
void Swarm::manage_resynchronization(){
  //---------------------------

  for(int i=0; i<struct_k4n->list_master.size(); i++){
    k4n::dev::Master* master = *std::next(struct_k4n->list_master.begin(), i);
    master->manage_resynchronization();
  }

  //---------------------------
}
void Swarm::close_master(k4n::dev::Master* master){
  //---------------------------

  sce_set->delete_entity_all(master);
  struct_k4n->list_master.remove(master);

  //---------------------------
}
void Swarm::close_all_master(){
  //---------------------------

  for(int i=0; i<struct_k4n->list_master.size(); i++){
    k4n::dev::Master* master = *std::next(struct_k4n->list_master.begin(), i);
    sce_set->delete_entity_all(master);
  }

  //---------------------------
}
k4n::dev::Master* Swarm::get_or_create_master(string name){
  utl::type::Set* set_scene = sce_database->get_set_scene();
  //---------------------------

  //Check if already existing
  for(int i=0; i<struct_k4n->list_master.size(); i++){
    k4n::dev::Master* master = *std::next(struct_k4n->list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //Create the master
  k4n::dev::Master* master = new k4n::dev::Master();
  master->name = name;
  master->is_lockable = true;
  sce_set->add_subset(set_scene, master);
  struct_k4n->list_master.push_back(master);
  struct_k4n->selected_master = master;

  //---------------------------
  return master;
}
k4n::dev::Master* Swarm::get_master_by_name(string name){
  //---------------------------

  //Check if already existing
  for(int i=0; i<struct_k4n->list_master.size(); i++){
    k4n::dev::Master* master = *std::next(struct_k4n->list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //---------------------------
  return nullptr;
}
k4n::dev::Master* Swarm::get_selected_master(){
  return struct_k4n->selected_master;
}
list<k4n::dev::Master*>& Swarm::get_list_master(){
  return struct_k4n->list_master;
}

}
