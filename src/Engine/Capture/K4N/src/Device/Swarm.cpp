#include "Swarm.h"

#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>


namespace eng::k4n::dev{

//Constructor / Destructor
Swarm::Swarm(eng::k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  eng::scene::Node* node_scene = node_engine->get_node_scene();
  prf::Node* node_profiler = node_engine->get_node_profiler();

  this->node_k4n = node_k4n;
  this->profiler = node_profiler->get_profiler();
  this->sce_scene = node_scene->get_scene();
  this->k4n_transfo = new eng::k4n::utils::Transformation();

  //---------------------------
}
Swarm::~Swarm(){}

//Main function
void Swarm::init_scene(){
  //---------------------------

  //If no real device create playback
  eng::k4n::dev::Master* master = get_or_create_master("Master");
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
  file_4.path_data = "/home/aether/Desktop/cerfav_8.mkv";

  //Create playback list
  this->create_sensor_playback(file_3);
  //this->create_sensor_playback(file_2);

  //---------------------------
}
void Swarm::update_profiler(){
  //---------------------------
sayHello();

  //---------------------------
}

//Sensor function
void Swarm::create_sensor_playback(utl::media::File& file){
  if(!utl::fct::file::is_file_exist(file.path_data)) return;
  //---------------------------

  //Associated master
  eng::k4n::dev::Master* master = selected_master;
  int index = master->get_nb_entity();

  //Sensor creation
  eng::k4n::dev::Sensor* sensor = new eng::k4n::dev::Sensor(node_k4n);
  sensor->name = "playback_" + to_string(index);
  sensor->param.format = utl::fct::info::get_format_from_path(file.path_data);
  sensor->param.index = index;
  sensor->param.is_playback = true;
  sensor->param.path_data = file.path_data;
  sensor->param.path_transfo = file.path_transfo;
  sensor->master = master;

  //Sensor initialization
  master->insert_sensor(sensor);
  sensor->init();
  sce_scene->assign_entity_UID(sensor);
  k4n_transfo->find_transformation_from_file(sensor, file.path_transfo);

  //---------------------------
}
void Swarm::create_sensor_capture(){
  //---------------------------

  //Associated master
  eng::k4n::dev::Master* master = get_or_create_master("Capture");
  int index = master->get_nb_entity();

  //Sensor creation
  eng::k4n::dev::Sensor* sensor = new eng::k4n::dev::Sensor(node_k4n);
  sensor->name = "capture_" + to_string(index);
  sensor->param.index = index;
  sensor->param.is_playback = false;
  sensor->master = master;

  //Sensor initialization
  master->insert_sensor(sensor);
  sce_scene->assign_entity_UID(sensor);
  sensor->init();
  sensor->run_capture();

  //---------------------------
}

//Sensor function
void Swarm::close_master(eng::k4n::dev::Master* master){
  //---------------------------

  master->delete_entity_all();
  this->list_master.remove(master);

  //---------------------------
}
eng::k4n::dev::Master* Swarm::get_or_create_master(string name){
  utl::type::Set* set_scene = sce_scene->get_set_scene();
  //---------------------------

  //Check if already existing
  for(int i=0; i<list_master.size(); i++){
    eng::k4n::dev::Master* master = *std::next(list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //Create the master
  eng::k4n::dev::Master* master = new eng::k4n::dev::Master();
  master->name = name;
  master->is_lockable = true;
  set_scene->add_set(master);
  this->list_master.push_back(master);
  this->selected_master = master;

  //---------------------------
  return master;
}
eng::k4n::dev::Master* Swarm::get_master_by_name(string name){
  //---------------------------

  //Check if already existing
  for(int i=0; i<list_master.size(); i++){
    eng::k4n::dev::Master* master = *std::next(list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //---------------------------
  return nullptr;
}

}
