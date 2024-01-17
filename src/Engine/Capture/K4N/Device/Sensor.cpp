#include "Sensor.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4N/Thread/K4A_capture.h>
#include <Engine/Capture/K4N/Thread/K4A_playback.h>


namespace k4n::dev{


//Constructor / Destructor
Sensor::Sensor(Engine* engine){
  //---------------------------

  eng::scene::Node* node_scene = engine->get_node_scene();

  this->engine = engine;
  this->k4a_capture = new K4A_capture(engine);
  this->k4a_playback = new K4A_playback(engine);
  this->eng_scene = node_scene->get_scene();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->ope_transform = new eng::ope::Transformation();

  this->device_type = "k4n::device::Sensor";

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  this->destroy();

  //---------------------------
}

//Main function
void Sensor::init(){
  //---------------------------

  //Sensor name
  string str_mode = device.is_playback ? "playback_" : "capture_";
  this->device.name = str_mode + to_string(device.index);

  //Sensor cloud
  object = new entity::Object(engine);
  object->name = device.name;
  object->data->draw_type_name = "point";
  eng_scene->insert_object(object);

  //---------------------------
}
void Sensor::reset(){
  //---------------------------

  object->reset_entity();

  //---------------------------
}
void Sensor::destroy(){
  //---------------------------

  this->stop_threads();
  this->device.transformation.destroy();
  eng_scene->remove_object(object);

  //---------------------------
}
void Sensor::draw_cloud(){
  //---------------------------

  std::unique_lock<std::mutex> lock(object->data->mutex);
  object->data->nb_point = object->data->xyz.size();
  eng_scene->update_data(object->data);

  //---------------------------
}

//Player function
void Sensor::set_play(){
  //---------------------------


  //---------------------------
}

//Capture function
void Sensor::run_capture(){
  //---------------------------

  if(!k4a_capture->is_thread_running()){
    k4a_capture->start_thread(this);
  }

  //---------------------------
}
void Sensor::restart_capture(){
  //---------------------------

  this->stop_threads();
  this->run_capture();

  //---------------------------
}
void Sensor::run_playback(string path){
  //---------------------------

  this->playback.path = path;
  k4a_playback->start_thread(this);

  //---------------------------
}
void Sensor::stop_threads(){
  //---------------------------

  this->k4a_capture->stop_thread();
  this->k4a_playback->stop_thread();

  //---------------------------
}
void Sensor::reset_color_configuration(){
  //---------------------------

  color.config.exposure.value = 15625;
  color.config.white_balance.value = 4500;
  color.config.brightness.value = 128;
  color.config.contrast.value = 5;
  color.config.saturation.value = 32;
  color.config.sharpness.value = 2;
  color.config.gain.value = 0;
  color.config.backlight_compensation.value = 0;
  color.config.power_frequency.value = 2;

  //---------------------------
}


}
