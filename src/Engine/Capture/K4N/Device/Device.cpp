#include "Device.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4N/Thread/K4A_capture.h>
#include <Engine/Capture/K4N/Thread/K4A_playback.h>


namespace k4n{


//Constructor / Destructor
Device::Device(Engine* engine){
  //---------------------------

  eng::scene::Node* node_scene = engine->get_node_scene();

  this->engine = engine;
  this->k4a_capture = new K4A_capture(engine);
  this->k4a_playback = new K4A_playback(engine);
  this->eng_scene = node_scene->get_scene();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->ope_transform = new eng::ope::Transformation();

  this->type = "Device";

  //---------------------------
}
Device::~Device(){
  //---------------------------

  this->destroy();

  //---------------------------
}

//Main function
void Device::init(){
  //---------------------------

  //Device name
  string str_mode = device.is_playback ? "playback_" : "capture_";
  this->device.name = str_mode + to_string(device.index);

  //Device cloud
  cloud.object = new eng::data::Object(engine);
  cloud.object->name = device.name;
  cloud.object->draw_type_name = "point";
  eng_scene->insert_object(cloud.object);

  //---------------------------
}
void Device::update_entity(){
  eng::camera::Node* node_camera = engine->get_node_camera();
  eng::camera::Control* cam_control = node_camera->get_camera_control();
  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  //----------------------------

  cam_control->compute_camera_mvp(cloud.object);
  sce_glyph->update_glyph_object(cloud.object);

  //----------------------------
}
void Device::reset(){
  //---------------------------

  cloud.object->reset();

  //---------------------------
}
void Device::destroy(){
  //---------------------------

  this->stop_threads();
  this->device.transformation.destroy();
  eng_scene->remove_object(cloud.object);

  //---------------------------
}
void Device::draw_cloud(){
  //---------------------------

  std::unique_lock<std::mutex> lock(cloud.object->mutex);
  cloud.object->nb_point = cloud.object->xyz.size();
  eng_scene->update_object(cloud.object);

  //---------------------------
}

//Capture function
void Device::run_capture(){
  //---------------------------

  if(!k4a_capture->is_thread_running()){
    k4a_capture->start_thread(this);
  }

  //---------------------------
}
void Device::restart_capture(){
  //---------------------------

  this->stop_threads();
  this->run_capture();

  //---------------------------
}
void Device::run_playback(string path){
  //---------------------------

  this->playback.path = path;
  k4a_playback->start_thread(this);

  //---------------------------
}
void Device::stop_threads(){
  //---------------------------

  this->k4a_capture->stop_thread();
  this->k4a_playback->stop_thread();

  //---------------------------
}
void Device::reset_color_configuration(){
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
