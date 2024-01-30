#include "Swarm.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::k4n::dev{

//Constructor / Destructor
Swarm::Swarm(eng::k4n::Node* node_k4n){
  //---------------------------

  eng::Node* engine = node_k4n->get_node_engine();
  eng::scene::Node* sce_node = engine->get_node_scene();

  this->node_k4n = node_k4n;
  this->sce_scene = sce_node->get_scene();
  this->k4n_transfo = new eng::k4n::utils::Transformation();

  //---------------------------
}
Swarm::~Swarm(){}

//Main function
void Swarm::init_scene(){
  //---------------------------

  //If no real device create playback
  eng::k4n::dev::Master* master = get_or_create_master("versaille");
  uint32_t current_nb_dev = k4a_device_get_installed_count();
  if(current_nb_dev != 0) return;

  utl::media::File file_1;
  file_1.path_data = "/home/aether/Desktop/versaille_0.mkv";
  file_1.path_transfo = "/home/aether/Desktop/versaille_0.json";

  utl::media::File file_2;
  file_2.path_data = "/home/aether/Desktop/versaille_2.mkv";
  file_2.path_transfo = "/home/aether/Desktop/versaille_2.json";

  //Create playback list
  this->create_sensor_playback(file_1);
  this->create_sensor_playback(file_2);

  //---------------------------
}

//Sensor function
void Swarm::create_sensor_playback(utl::media::File& file){
  if(!utl::fct::file::is_file_exist(file.path_data)) return;
  //---------------------------

  //Associated master
  eng::k4n::dev::Master* master = selected_master;
  int index = master->list_sensor.size();

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
  master->insert_sensor_playback(sensor);
  sensor->init();
  sce_scene->assign_entity_UID(sensor);
  k4n_transfo->find_transformation_from_file(sensor, file.path_transfo);

  //---------------------------
}
void Swarm::create_sensor_capture(){
  //---------------------------

  //Associated master
  eng::k4n::dev::Master* master = get_or_create_master("Capture");
  int index = master->list_sensor.size();

  //Sensor creation
  eng::k4n::dev::Sensor* sensor = new eng::k4n::dev::Sensor(node_k4n);
  sensor->name = "capture_" + to_string(index);
  sensor->param.index = index;
  sensor->param.is_playback = false;
  sensor->master = master;

  //Sensor initialization
  master->insert_sensor_capture(sensor);
  sce_scene->assign_entity_UID(sensor);
  sensor->init();
  sensor->run_capture();

  //---------------------------
}

//Sensor function
void Swarm::close_master(eng::k4n::dev::Master* master){
  //---------------------------

  master->delete_all_sensor();
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
