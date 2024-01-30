#include "Swarm.h"

#include <Engine/Node.h>
#include <Utility/Namespace.h>
#include <Engine/Capture/K4N/Namespace.h>

/*
  Manage list<master> which is include in list<Set> of set_scene
*/

namespace eng::k4n::dev{

//Constructor / Destructor
Swarm::Swarm(eng::k4n::Node* k4n_node){
  //---------------------------

  eng::Node* engine = k4n_node->get_node_engine();
  eng::scene::Node* sce_node = engine->get_node_scene();

  this->k4n_node = k4n_node;
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
  //this->create_sensor_playback(file_2);

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
  eng::k4n::dev::Sensor* sensor = new eng::k4n::dev::Sensor(k4n_node);
  sensor->name = "playback_" + to_string(index);
  sensor->param.format = utl::fct::info::get_format_from_path(file.path_data);
  sensor->param.index = index;
  sensor->param.is_playback = true;
  sensor->param.path_data = file.path_data;
  sensor->param.path_transfo = file.path_transfo;
  sensor->master = master;

  //Sensor initialization
  this->selected_sensor = sensor;
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
  eng::k4n::dev::Sensor* sensor = new eng::k4n::dev::Sensor(k4n_node);
  sensor->name = "capture_" + to_string(index);
  sensor->param.index = index;
  sensor->param.is_playback = false;
  sensor->master = master;

  //Sensor initialization
  this->selected_sensor = sensor;
  master->insert_sensor_capture(sensor);
  sce_scene->assign_entity_UID(sensor);
  sensor->init();
  sensor->run_capture();

  //---------------------------
}
void Swarm::close_selected_sensor(){
  eng::k4n::dev::Sensor* sensor = selected_sensor;
  eng::k4n::dev::Master* master = sensor->master;
  //---------------------------

  this->selecte_next_sensor();
  master->delete_sensor(sensor);

  //---------------------------
}
void Swarm::close_sensor_all(eng::k4n::dev::Master* master){
  //---------------------------

  for(int j=0; j<master->list_sensor.size(); j++){
    eng::k4n::dev::Sensor* sensor = *std::next(master->list_sensor.begin(), j);
    sensor->remove_entity();
  }

  //---------------------------
}
void Swarm::selecte_next_sensor(){
  //---------------------------
/*
  if(list_sensor.size() == 0){
    selected_sensor = nullptr;
  }else{
    selected_sensor = *std::next(list_sensor.begin(), 0);
  }
*/
  //---------------------------
}

//Sensor function
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
