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
  this->sce_scene = node_scene->get_scene();
  this->k4n_transfo = new k4n::utils::Transformation();

  //---------------------------
}
Swarm::~Swarm(){}

//Main function
void Swarm::init_scene(){
  //---------------------------

  //If no real device create playback
  k4n::dev::Master* master = get_or_create_master("Master");
  uint32_t current_nb_dev = k4a_device_get_installed_count();
  if(current_nb_dev != 0) return;

  utl::media::File file_1;
  file_1.path_data = "/home/aether/Desktop/versaille_0.mkv";
  file_1.path_transfo = "/home/aether/Desktop/versaille_0.json";

  utl::media::File file_2;
  file_2.path_data = "/home/aether/Desktop/versaille_2.mkv";
  file_2.path_transfo = "/home/aether/Desktop/versaille_2.json";

  utl::media::File file_3;
  file_3.path_data = "/home/aether/Desktop/output.mkv";

  utl::media::File file_4;
  file_4.path_data = "/home/aether/Desktop/cerfav_3_1.mkv";

  //Create playback list
  this->create_sensor_playback(file_1);
  //this->create_sensor_playback(file_2);
  //this->create_sensor_playback(file_4);

  //---------------------------
}

//Sensor function
void Swarm::create_sensor_playback(utl::media::File& file){
  if(!utl::fct::file::is_file_exist(file.path_data)) return;
  //---------------------------

  //Associated master
  k4n::dev::Master* master = struct_k4n->selected_master;
  int index = master->get_nb_entity();

  //Sensor creation
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(struct_k4n);
  sensor->name = "playback_" + to_string(index);
  sensor->param.format = utl::fct::info::get_format_from_path(file.path_data);
  sensor->param.file_size = utl::fct::info::get_file_size(file.path_data);
  sensor->param.index = index;
  sensor->param.mode = k4n::mode::PLAYBACK;
  sensor->param.path_file = file.path_data;
  sensor->param.path_transfo = file.path_transfo;
  sensor->master = master;

  //Sensor initialization
  sensor->init();
  master->insert_sensor(sensor);
  sce_scene->assign_entity_UID(sensor);
  k4n_transfo->find_transformation_from_file(sensor, file.path_transfo);

  //---------------------------
}
void Swarm::create_sensor_capture(){
  //---------------------------

  //Associated master
  k4n::dev::Master* master = get_or_create_master("Capture");
  int index = master->get_nb_entity();

  //Sensor creation
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(struct_k4n);
  sensor->name = "capture_" + to_string(index);
  sensor->param.index = index;
  sensor->param.mode = k4n::mode::CAPTURE;
  sensor->master = master;

  //Sensor initialization
  sensor->init();
  master->insert_sensor(sensor);
  sce_scene->assign_entity_UID(sensor);
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

  master->delete_entity_all();
  struct_k4n->list_master.remove(master);

  //---------------------------
}
void Swarm::close_all_master(){
  //---------------------------

  for(int i=0; i<struct_k4n->list_master.size(); i++){
    k4n::dev::Master* master = *std::next(struct_k4n->list_master.begin(), i);
    master->delete_entity_all();
  }

  //---------------------------
}
k4n::dev::Master* Swarm::get_or_create_master(string name){
  utl::type::Set* set_scene = sce_scene->get_set_scene();
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
  set_scene->add_set(master);
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
