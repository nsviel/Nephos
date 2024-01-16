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
  this->struct_swarm = new k4n::structure::Swarm();
  this->k4n_transfo = new k4n::utils::Transformation();
  this->default_folder = "../media/record/";
  this->default_file = "/home/aether/Desktop/versaille_with_transfo_mat.mkv";

  //---------------------------
}
Swarm::~Swarm(){}

//Main function
void Swarm::draw_all_clouds(){
  list<k4n::dev::Sensor*>& list_device = struct_swarm->list_sensor;
  //---------------------------

  //Run all thread
  for(int i=0; i<list_device.size(); i++){
    k4n::dev::Sensor* k4n_sensor = *std::next(list_device.begin(), i);
    k4n_sensor->draw_cloud();
  }

  //---------------------------
}
void Swarm::init_scene(){
  //---------------------------

  //If no real device create virtual one
  uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device == 0 && struct_swarm->nb_playback == 0){
    this->create_device_playback(default_file);
  }

  //---------------------------
}

//Connection function
void Swarm::refresh_connected_device(){
  //---------------------------

  const uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device != struct_swarm->nb_device){
    //If some news, run them
    if(nb_device > struct_swarm->nb_device){
      int number = nb_device - struct_swarm->nb_device;
      this->manage_new_capture_device(number);
    }
    //If some less, supress them
    else if(nb_device < struct_swarm->nb_device){
      int number = struct_swarm->nb_device - nb_device;
      this->manage_less_capture_device(number);
    }

    struct_swarm->nb_device = nb_device;
  }

  //---------------------------
}
void Swarm::manage_new_capture_device(int nb_new_device){
  list<k4n::dev::Sensor*>& list_device = struct_swarm->list_sensor;
  //---------------------------

  //If previsouly no device, we need to supress all default playback
  if(struct_swarm->nb_device == 0){
    this->close_device_all();
  }

  //Create required number of new devices
  for(int i=0; i<nb_new_device; i++){
    this->create_device_capture();
  }

  //---------------------------
}
void Swarm::manage_less_capture_device(int nb_less_device){
  //---------------------------

  //Suppress all devices
  this->close_device_all();

  //If no real device create virtual one
  uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device != 0){
    for(int i=0; i<nb_device; i++){
      this->create_device_capture();
    }
  }

  //---------------------------
}

//Creation / supression function
k4n::dev::Sensor* Swarm::create_device_playback(string path){
  //---------------------------

  k4n::dev::Sensor* k4n_sensor = new k4n::dev::Sensor(engine);
  k4n_sensor->name = "playback_" + to_string(struct_swarm->nb_device);
  k4n_sensor->device.index = struct_swarm->nb_device;
  k4n_sensor->device.is_playback = true;
  k4n_sensor->playback.path = path;
  k4n_sensor->playback.filename = info::get_filename_from_path(path);
  k4n_sensor->recorder.folder = default_folder;
  k4n_sensor->recorder.path = default_folder + "record_dev_" + to_string(k4n_sensor->device.index) + ".mkv";

  struct_swarm->selected_device = k4n_sensor;
  struct_swarm->list_sensor.push_back(k4n_sensor);
  struct_swarm->nb_playback++;

  k4n_sensor->init();
  k4n_sensor->run_playback(path);
  sce_scene->insert_entity_scene(k4n_sensor);

  k4n_transfo->truc(path);

  //---------------------------
  return k4n_sensor;
}
k4n::dev::Sensor* Swarm::create_device_capture(){
  //---------------------------

  k4n::dev::Sensor* k4n_sensor = new k4n::dev::Sensor(engine);
  k4n_sensor->name = "device_" + to_string(struct_swarm->nb_capture);
  k4n_sensor->device.index = struct_swarm->nb_capture;
  k4n_sensor->device.is_playback = false;
  k4n_sensor->recorder.folder = default_folder;
  k4n_sensor->recorder.path = default_folder + "record_dev_" + to_string(k4n_sensor->device.index) + ".mkv";

  struct_swarm->selected_device = k4n_sensor;
  struct_swarm->list_sensor.push_back(k4n_sensor);
  struct_swarm->nb_capture++;

  k4n_sensor->init();
  k4n_sensor->run_capture();
  sce_scene->insert_entity_scene(k4n_sensor);

  //---------------------------
  return k4n_sensor;
}
void Swarm::close_device(k4n::dev::Sensor* k4n_sensor){
  list<k4n::dev::Sensor*>& list_device = struct_swarm->list_sensor;
  //---------------------------

  k4n_sensor->destroy();
  list_device.remove(k4n_sensor);
  k4n_sensor->device.is_playback ? struct_swarm->nb_playback-- : struct_swarm->nb_capture--;
  delete(k4n_sensor);
  k4n_sensor = nullptr;

  this->selecte_next_device();

  //---------------------------
}
void Swarm::close_device_all(){
  list<k4n::dev::Sensor*>& list_device = struct_swarm->list_sensor;
  //---------------------------

  for(int i=0; i<list_device.size(); i++){
    k4n::dev::Sensor* k4n_sensor = *std::next(list_device.begin(), i);
    this->close_device(k4n_sensor);
  }

  //---------------------------
}
void Swarm::selecte_next_device(){
  list<k4n::dev::Sensor*>& list_device = struct_swarm->list_sensor;
  //---------------------------

  if(list_device.size() == 0){
    struct_swarm->selected_device = nullptr;
  }else{
    struct_swarm->selected_device = *std::next(list_device.begin(), 0);
  }

  //---------------------------
}

}
