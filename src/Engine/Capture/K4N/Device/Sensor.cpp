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
  this->sce_scene = node_scene->get_scene();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->ope_transform = new eng::ope::Transformation();

  this->type = "k4n::device::Sensor";
  this->icon = ICON_FA_CAMERA_RETRO;

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  this->remove_entity();

  //---------------------------
}

//Main function
void Sensor::init(){
  //---------------------------

  //Sensor name
  string str_mode = param.is_playback ? "playback_" : "capture_";
  this->param.name = str_mode + to_string(param.index);

  //Sensor cloud
  object = new entity::Object(engine);
  object->name = param.name;
  object->data->draw_type_name = "point";
  sce_scene->init_entity(object);

  //---------------------------
}
void Sensor::reset(){
  //---------------------------

  object->reset_entity();

  //---------------------------
}

//Entity function
void Sensor::update_entity(){
  //----------------------------

  //Retrieve capture data
  std::unique_lock<std::mutex> lock(object->data->mutex);
  object->data->nb_point = object->data->xyz.size();
  object->update_entity();

  //----------------------------
}
void Sensor::remove_entity(){
  eng::capture::Node* node_capture = engine->get_node_capture();
  k4n::Node* node_kinect = node_capture->get_node_kinect();
  k4n::dev::Swarm* k4n_swarm = node_kinect->get_k4n_swarm();
  //---------------------------

  //First, destroy own elements
  this->stop_threads();
  this->param.transformation.destroy();
  this->object->remove_entity();

  //Second, delete set references
  master->delete_entity(this);
  k4n_swarm->close_sensor(master, this);

  //---------------------------
}
void Sensor::visibility_entity(bool value){
  //---------------------------

  this->is_visible = value;
  object->data->is_visible = value;
  object->visibility_entity(value);

  //---------------------------
}
void Sensor::reset_entity(){
  //---------------------------

  object->reset_entity();

  //---------------------------
}

//Capture function
void Sensor::run_capture(){
  //---------------------------

  this->stop_threads();
  k4a_capture->start_thread(this);

  //---------------------------
}
void Sensor::run_playback(string path){
  //---------------------------

  this->stop_threads();
  this->param.file_path = path;
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
