#include "Swarm.h"

#include <Engine/Engine.h>
#include <Utility/Function/File/Info.h>


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
void Swarm::draw_all_clouds(){
  //---------------------------

  for(int i=0; i<list_master.size(); i++){
    k4n::dev::Master* master = *std::next(list_master.begin(), i);
    for(int j=0; j<master->list_sensor.size(); j++){
      k4n::dev::Sensor* sensor = *std::next(master->list_sensor.begin(), j);
      sensor->draw_cloud();
    }
  }

  //---------------------------
}
void Swarm::init_scene(){
  string path = "/home/aether/Desktop/versaille_1.mkv";
  //---------------------------

  //If no real device create virtual one
  string name = info::get_name_from_path(path);
  k4n::dev::Master* master = get_or_create_master(name);
  uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device == 0 && nb_dev_playback == 0){
    this->create_sensor_playback(master, path);
  }

  //---------------------------
}

//Sensor function
void Swarm::create_sensor_playback(k4n::dev::Master* master, string path){
  if(!file::is_file_exist(path)) return;
  //---------------------------

  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(engine);
  sensor->name = "playback_" + to_string(nb_dev_capture);
  sensor->device.index = nb_dev_capture;
  sensor->device.is_playback = true;
  sensor->playback.path = path;
  sensor->playback.filename = info::get_filename_from_path(path);
  sensor->master = master;

  this->selected_sensor = sensor;
  master->list_sensor.push_back(sensor);
  nb_dev_playback++;

  sensor->init();
  sensor->run_playback(path);

  k4n_transfo->truc(path);

  //---------------------------
}
void Swarm::create_sensor_playback(string path){
  if(!file::is_file_exist(path)) return;
  //---------------------------

  k4n::dev::Master* master = selected_master;

  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(engine);
  sensor->name = "playback_" + to_string(nb_dev_capture);
  sensor->device.index = nb_dev_capture;
  sensor->device.is_playback = true;
  sensor->playback.path = path;
  sensor->playback.filename = info::get_filename_from_path(path);
  sensor->master = master;

  this->selected_sensor = sensor;
  master->list_sensor.push_back(sensor);
  nb_dev_playback++;

  sensor->init();
  sensor->run_playback(path);

  k4n_transfo->truc(path);

  //---------------------------
}
void Swarm::create_sensor_capture(k4n::dev::Master* master){
  //---------------------------

  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(engine);
  sensor->name = "device_" + to_string(nb_dev_capture);
  sensor->device.index = nb_dev_capture;
  sensor->device.is_playback = false;
  sensor->master = master;

  this->selected_sensor = sensor;
  master->list_sensor.push_back(sensor);
  nb_dev_capture++;

  sensor->init();
  sensor->run_capture();

  //---------------------------
}
void Swarm::close_sensor(k4n::dev::Master* master, k4n::dev::Sensor* sensor){
  //---------------------------

  for(int i=0; i<master->list_sensor.size(); i++){
    k4n::dev::Sensor* sensor_in_list = *std::next(master->list_sensor.begin(), i);
    if(sensor->UID == sensor_in_list->UID){
      sensor->destroy();
      master->list_sensor.remove(sensor);
      sensor->device.is_playback ? nb_dev_playback-- : nb_dev_capture--;
      delete(sensor);
      sensor = nullptr;
    }
  }

  //a revoir
  if(master->list_sensor.size() == 0){
    selected_sensor = nullptr;
  }
  this->selecte_next_sensor();

  //---------------------------
}
void Swarm::close_sensor_all(){
  //---------------------------

  for(int i=0; i<list_master.size(); i++){
    k4n::dev::Master* master = *std::next(list_master.begin(), i);
    for(int j=0; j<master->list_sensor.size(); j++){
      k4n::dev::Sensor* sensor = *std::next(master->list_sensor.begin(), j);
      this->close_sensor(sensor->master, sensor);
    }
  }

  //---------------------------
}
void Swarm::close_sensor_all(k4n::dev::Master* master){
  //---------------------------

  for(int j=0; j<master->list_sensor.size(); j++){
    k4n::dev::Sensor* sensor = *std::next(master->list_sensor.begin(), j);
    this->close_sensor(master, sensor);
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
  //---------------------------

  //Check if already existing
  for(int i=0; i<list_master.size(); i++){
    k4n::dev::Master* master = *std::next(list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //Create the master
  k4n::dev::Master* master = new k4n::dev::Master(engine);
  master->name = name;
  sce_scene->insert_entity_scene(master);
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
