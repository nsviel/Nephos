#include "Swarm.h"

#include <Engine/Engine.h>
#include <Utility/Function/File/Info.h>

/*
  Manage list<master> which is include in list<Set> of set_scene
*/

namespace k4n::dev{

//Constructor / Destructor
Swarm::Swarm(Engine* engine){
  //---------------------------

  eng::scene::Node* node_scene = engine->get_node_scene();

  this->engine = engine;
  this->sce_scene = node_scene->get_scene();
  this->k4n_transfo = new k4n::utils::Transformation();

  //---------------------------
}
Swarm::~Swarm(){}

//Main function
void Swarm::init_scene(){
  //---------------------------

  utl::media::File file_1;
  file_1.path_data = "/home/aether/Desktop/versaille_0.mkv";
  file_1.path_transfo = "/home/aether/Desktop/versaille_0.json";

  utl::media::File file_2;
  file_2.path_data = "/home/aether/Desktop/versaille_2.mkv";
  file_2.path_transfo = "/home/aether/Desktop/versaille_2.json";

  //If no real device create virtual one
  k4n::dev::Master* master = get_or_create_master("versaille");
  uint32_t current_nb_dev = k4a_device_get_installed_count();
  if(current_nb_dev != 0) return;

  //Create playback list
  this->create_sensor_playback(master, file_1);
  this->create_sensor_playback(master, file_2);

  //---------------------------
}

//Sensor function
void Swarm::create_sensor_playback(k4n::dev::Master* master, utl::media::File& file){
  if(!file::is_file_exist(file.path_data)) return;
  if(!file::is_file_exist(file.path_transfo)) return;
  //---------------------------

  int index = master->list_sensor.size();
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(engine);
  sensor->name = "playback_" + to_string(index);
  sensor->param.index = index;
  sensor->param.is_playback = true;
  sensor->param.path_data = file.path_data;
  sensor->param.file_name = info::get_filename_from_path(file.path_data);
  sensor->param.path_transfo = file.path_transfo;
  sensor->master = master;

  this->selected_sensor = sensor;
  master->insert_sensor_playback(sensor);

  sensor->init();
  sce_scene->assign_entity_UID(sensor);
  k4n_transfo->find_transformation_from_file(sensor, file.path_transfo);

  //---------------------------
}
void Swarm::create_sensor_playback(k4n::dev::Master* master, string path){
  if(!file::is_file_exist(path)) return;
  //---------------------------

  int index = master->list_sensor.size();
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(engine);
  sensor->name = "playback_" + to_string(index);
  sensor->param.index = index;
  sensor->param.is_playback = true;
  sensor->param.path_data = path;
  sensor->param.file_name = info::get_filename_from_path(path);
  sensor->master = master;

  this->selected_sensor = sensor;
  master->insert_sensor_playback(sensor);

  sensor->init();
  sce_scene->assign_entity_UID(sensor);
  k4n_transfo->find_transformation_from_file(sensor, "");

  //---------------------------
}
void Swarm::create_sensor_playback(string path){
  if(!file::is_file_exist(path)) return;
  //---------------------------

  k4n::dev::Master* master = selected_master;

  int index = master->list_sensor.size();
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(engine);
  sensor->name = "playback_" + to_string(index);
  sensor->param.index = index;
  sensor->param.is_playback = true;
  sensor->param.path_data = path;
  sensor->param.file_name = info::get_filename_from_path(path);
  sensor->master = master;

  this->selected_sensor = sensor;
  master->insert_sensor_playback(sensor);

  sensor->init();
  sce_scene->assign_entity_UID(sensor);
  k4n_transfo->find_transformation_from_file(sensor, "");

  //---------------------------
}
void Swarm::create_sensor_capture(k4n::dev::Master* master){
  //---------------------------

  int index = master->list_sensor.size();
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(engine);
  sensor->name = "device_" + to_string(index);
  sensor->param.index = index;
  sensor->param.is_playback = false;
  sensor->master = master;

  this->selected_sensor = sensor;
  master->insert_sensor_capture(sensor);
  sce_scene->assign_entity_UID(sensor);

  sensor->init();
  sensor->run_capture();

  //---------------------------
}
void Swarm::close_sensor_all(k4n::dev::Master* master){
  //---------------------------

  for(int j=0; j<master->list_sensor.size(); j++){
    k4n::dev::Sensor* sensor = *std::next(master->list_sensor.begin(), j);
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
k4n::dev::Master* Swarm::get_or_create_master(string name){
  utl::type::Set* set_scene = sce_scene->get_set_scene();
  //---------------------------

  //Check if already existing
  for(int i=0; i<list_master.size(); i++){
    k4n::dev::Master* master = *std::next(list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //Create the master
  k4n::dev::Master* master = new k4n::dev::Master();
  master->name = name;
  master->is_lockable = true;
  set_scene->add_set(master);
  this->list_master.push_back(master);
  this->selected_master = master;

  //---------------------------
  return master;
}
k4n::dev::Master* Swarm::get_master_by_name(string name){
  //---------------------------

  //Check if already existing
  for(int i=0; i<list_master.size(); i++){
    k4n::dev::Master* master = *std::next(list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //---------------------------
  return nullptr;
}

}
