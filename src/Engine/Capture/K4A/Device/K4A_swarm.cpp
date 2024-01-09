#include "K4A_swarm.h"

#include <Engine/Engine.h>
#include <Utility/Function/File/Info.h>


//Constructor / Destructor
K4A_swarm::K4A_swarm(Engine* engine){
  //---------------------------

  eng::scene::Node* eng_data = engine->get_eng_data();

  this->engine = engine;
  this->eng_scene = eng_data->get_eng_scene();
  this->str_swarm = new eng::kinect::structure::Swarm();
  this->default_folder = "../media/record/";
  this->default_file = "/home/aether/Desktop/versaille.mkv";

  //---------------------------
}
K4A_swarm::~K4A_swarm(){}

//Main function
void K4A_swarm::draw_all_clouds(){
  list<K4A_device*>& list_device = str_swarm->list_device;
  //---------------------------

  //Run all thread
  for(int i=0; i<list_device.size(); i++){
    K4A_device* k4a_device = *std::next(list_device.begin(), i);
    k4a_device->draw_cloud();
  }

  //---------------------------
}
void K4A_swarm::reset_all_device(){
  list<K4A_device*>& list_device = str_swarm->list_device;
  //---------------------------

  //Run all thread
  for(int i=0; i<list_device.size(); i++){
    K4A_device* k4a_device = *std::next(list_device.begin(), i);
    k4a_device->player.ts_seek = k4a_device->player.ts_beg;
  }

  //---------------------------
}

//Connection function
void K4A_swarm::refresh_connected_device(){
  //---------------------------

  const uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device != str_swarm->nb_device){
    //If some news, run them
    if(nb_device > str_swarm->nb_device){
      int number = nb_device - str_swarm->nb_device;
      this->manage_new_device(number);
    }
    //If some less, supress them
    else if(nb_device < str_swarm->nb_device){
      int number = str_swarm->nb_device - nb_device;
      this->manage_less_device(number);
    }

    str_swarm->nb_device = nb_device;
  }

  this->manage_no_device();

  //---------------------------
}
void K4A_swarm::manage_new_device(int nb_new_device){
  list<K4A_device*>& list_device = str_swarm->list_device;
  //---------------------------

  //If previsouly no device, we need to supress all default playback
  if(str_swarm->nb_device == 0){
    this->delete_device_all();
  }

  //Create required number of new devices
  for(int i=0; i<nb_new_device; i++){
    this->create_device();
  }

  //---------------------------
}
void K4A_swarm::manage_less_device(int nb_less_device){
  //---------------------------

  //Suppress all devices
  this->delete_device_all();

  //If no real device create virtual one
  uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device != 0){
    for(int i=0; i<nb_device; i++){
      this->create_device();
    }
  }

  //---------------------------
}
void K4A_swarm::manage_no_device(){
  //---------------------------

  //If no real device create virtual one
  uint32_t nb_device = k4a_device_get_installed_count();
  if(nb_device == 0 && str_swarm->nb_playback == 0){
    this->create_playback(default_file);
  }

  //---------------------------
}

//Creation function
K4A_device* K4A_swarm::create_playback(string path){
  //---------------------------

  K4A_device* k4a_device = new K4A_device(engine);
  k4a_device->name = "playback_" + to_string(str_swarm->nb_device);
  k4a_device->device.index = str_swarm->nb_device;
  k4a_device->device.is_playback = true;
  k4a_device->playback.path = path;
  k4a_device->playback.filename = info::get_filename_from_path(path);
  k4a_device->recorder.folder = default_folder;
  k4a_device->recorder.path = default_folder + "record_dev_" + to_string(k4a_device->device.index) + ".mkv";

  str_swarm->selected_device = k4a_device;
  str_swarm->list_device.push_back(k4a_device);
  str_swarm->nb_playback++;

  k4a_device->init();
  k4a_device->run_playback(path);
  eng_scene->insert_entity_scene(k4a_device);

  //---------------------------
  return k4a_device;
}
K4A_device* K4A_swarm::create_device(){
  //---------------------------

  K4A_device* k4a_device = new K4A_device(engine);
  k4a_device->name = "device_" + to_string(str_swarm->nb_capture);
  k4a_device->device.index = str_swarm->nb_capture;
  k4a_device->device.is_playback = false;
  k4a_device->recorder.folder = default_folder;
  k4a_device->recorder.path = default_folder + "record_dev_" + to_string(k4a_device->device.index) + ".mkv";

  str_swarm->selected_device = k4a_device;
  str_swarm->list_device.push_back(k4a_device);
  str_swarm->nb_capture++;

  k4a_device->init();
  k4a_device->run_capture();
  eng_scene->insert_entity_scene(k4a_device);

  //---------------------------
  return k4a_device;
}
void K4A_swarm::delete_device(K4A_device* k4a_device){
  list<K4A_device*>& list_device = str_swarm->list_device;
  //---------------------------

  k4a_device->destroy();
  list_device.remove(k4a_device);
  k4a_device->device.is_playback ? str_swarm->nb_playback-- : str_swarm->nb_capture--;
  delete(k4a_device);
  k4a_device = nullptr;

  this->selecte_next_device();

  //---------------------------
}
void K4A_swarm::delete_device_all(){
  list<K4A_device*>& list_device = str_swarm->list_device;
  //---------------------------

  for(int i=0; i<list_device.size(); i++){
    K4A_device* k4a_device = *std::next(list_device.begin(), i);
    this->delete_device(k4a_device);
  }

  //---------------------------
}
void K4A_swarm::selecte_next_device(){
  list<K4A_device*>& list_device = str_swarm->list_device;
  //---------------------------

  if(list_device.size() == 0){
    str_swarm->selected_device = nullptr;
  }else{
    str_swarm->selected_device = *std::next(list_device.begin(), 0);
  }

  //---------------------------
}
