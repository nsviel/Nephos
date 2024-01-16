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
  list<k4n::dev::Sensor*>& list_device = list_sensor;
  //---------------------------

  //Run all thread
  for(int i=0; i<list_device.size(); i++){
    k4n::dev::Sensor* k4n_sensor = *std::next(list_device.begin(), i);
    k4n_sensor->draw_cloud();
  }

  //---------------------------
}
void Swarm::init_scene(){
  string path = "/home/aether/Desktop/versaille.mkv";
  //---------------------------

  //If no real device create virtual one
  uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device == 0 && nb_dev_playback == 0){
    this->create_sensor_playback(path);
  }

  //---------------------------
}

//Connection function
void Swarm::refresh_connected_sensor(){
  //---------------------------

  const uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device != nb_dev_capture){
    //If some news, run them
    if(nb_device > nb_dev_capture){
      int number = nb_device - nb_dev_capture;
      this->manage_new_capture_sensor(number);
    }
    //If some less, supress them
    else if(nb_device < nb_dev_capture){
      int number = nb_dev_capture - nb_device;
      this->manage_less_capture_sensor(number);
    }

    nb_dev_capture = nb_device;
  }

  //---------------------------
}
void Swarm::manage_new_capture_sensor(int nb_new_device){
  list<k4n::dev::Sensor*>& list_device = list_sensor;
  //---------------------------

  //If previsouly no device, we need to supress all default playback
  if(nb_dev_capture == 0){
    this->close_sensor_all();
  }

  //Create required number of new devices
  for(int i=0; i<nb_new_device; i++){
    this->create_sensor_capture();
  }

  //---------------------------
}
void Swarm::manage_less_capture_sensor(int nb_less_device){
  //---------------------------

  //Suppress all devices
  this->close_sensor_all();

  //If no real device create virtual one
  uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device != 0){
    for(int i=0; i<nb_device; i++){
      this->create_sensor_capture();
    }
  }

  //---------------------------
}

//Creation / supression function
k4n::dev::Sensor* Swarm::create_sensor_playback(string path){
  //---------------------------

  k4n::dev::Sensor* k4n_sensor = new k4n::dev::Sensor(engine);
  k4n_sensor->name = "playback_" + to_string(nb_dev_capture);
  k4n_sensor->device.index = nb_dev_capture;
  k4n_sensor->device.is_playback = true;
  k4n_sensor->playback.path = path;
  k4n_sensor->playback.filename = info::get_filename_from_path(path);

  selected_sensor = k4n_sensor;
  list_sensor.push_back(k4n_sensor);
  nb_dev_playback++;

  k4n_sensor->init();
  k4n_sensor->run_playback(path);
  sce_scene->insert_entity_scene(k4n_sensor);

  k4n_transfo->truc(path);

  //---------------------------
  return k4n_sensor;
}
k4n::dev::Sensor* Swarm::create_sensor_capture(){
  //---------------------------

  k4n::dev::Sensor* k4n_sensor = new k4n::dev::Sensor(engine);
  k4n_sensor->name = "device_" + to_string(nb_dev_capture);
  k4n_sensor->device.index = nb_dev_capture;
  k4n_sensor->device.is_playback = false;

  selected_sensor = k4n_sensor;
  list_sensor.push_back(k4n_sensor);
  nb_dev_capture++;

  k4n_sensor->init();
  k4n_sensor->run_capture();
  sce_scene->insert_entity_scene(k4n_sensor);

  //---------------------------
  return k4n_sensor;
}
void Swarm::close_sensor(k4n::dev::Sensor* k4n_sensor){
  list<k4n::dev::Sensor*>& list_device = list_sensor;
  //---------------------------

  k4n_sensor->destroy();
  list_device.remove(k4n_sensor);
  k4n_sensor->device.is_playback ? nb_dev_playback-- : nb_dev_capture--;
  delete(k4n_sensor);
  k4n_sensor = nullptr;

  this->selecte_next_sensor();

  //---------------------------
}
void Swarm::close_sensor_all(){
  list<k4n::dev::Sensor*>& list_device = list_sensor;
  //---------------------------

  for(int i=0; i<list_device.size(); i++){
    k4n::dev::Sensor* k4n_sensor = *std::next(list_device.begin(), i);
    this->close_sensor(k4n_sensor);
  }

  //---------------------------
}
void Swarm::selecte_next_sensor(){
  list<k4n::dev::Sensor*>& list_device = list_sensor;
  //---------------------------

  if(list_device.size() == 0){
    selected_sensor = nullptr;
  }else{
    selected_sensor = *std::next(list_device.begin(), 0);
  }

  //---------------------------
}

}
