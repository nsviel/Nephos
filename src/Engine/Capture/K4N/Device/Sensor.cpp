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

  this->type = "Sensor";

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

//Entity function
void Sensor::update_entity(){
  eng::camera::Node* node_camera = engine->get_node_camera();
  eng::camera::Control* cam_control = node_camera->get_camera_control();
  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  //----------------------------

  cam_control->compute_camera_mvp(object->data);
  sce_glyph->update_glyph_object(object);

  //----------------------------
}
void Sensor::remove_entity(){
  eng::capture::Node* node_capture = engine->get_node_capture();
  k4n::Node* node_kinect = node_capture->get_node_kinect();
  k4n::dev::Swarm* k4a_swarm = node_kinect->get_k4a_swarm();
  //---------------------------

  k4a_swarm->close_sensor(this, master);

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
  player.ts_seek = player.ts_beg;

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
