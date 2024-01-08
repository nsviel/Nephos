#include "K4A_device.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4A/Utils/Namespace.h>
#include <Engine/Capture/K4A/Thread/K4A_capture.h>
#include <Engine/Capture/K4A/Thread/K4A_playback.h>


//Constructor / Destructor
K4A_device::K4A_device(Engine* engine){
  //---------------------------

  eng::scene::Node* eng_data = engine->get_eng_data();

  this->k4a_capture = new K4A_capture(engine);
  this->k4a_playback = new K4A_playback(engine);
  this->eng_scene = eng_data->get_eng_scene();
  this->eng_glyph = eng_data->get_eng_glyph();
  this->ope_transform = new eng::ope::Transformation();

  //---------------------------
}
K4A_device::~K4A_device(){
  //---------------------------

  this->destroy();

  //---------------------------
}

//Main function
void K4A_device::init(){
  //---------------------------

  //Device name
  string str_mode = device.is_playback ? "playback_" : "capture_";
  this->device.name = str_mode + to_string(device.index);

  //Device cloud
  cloud.object = new eng::data::Object();
  cloud.object->name = device.name;
  cloud.object->draw_type_name = "point";
  eng_scene->insert_object_scene(cloud.object);

  //---------------------------
}
void K4A_device::destroy(){
  //---------------------------

  this->stop_threads();
  this->device.transformation.destroy();
  eng_scene->delete_object_scene(cloud.object);

  //---------------------------
}
void K4A_device::draw_cloud(){
  //---------------------------

  std::unique_lock<std::mutex> lock(cloud.object->mutex);
  cloud.object->nb_point = cloud.object->xyz.size();
  eng_scene->update_object(cloud.object);

  //---------------------------
}

//Capture function
void K4A_device::run_capture(){
  //---------------------------

  if(!k4a_capture->is_thread_running()){
    k4a_capture->start_thread(this);
  }

  //---------------------------
}
void K4A_device::restart_capture(){
  //---------------------------

  this->stop_threads();
  this->run_capture();

  //---------------------------
}
void K4A_device::run_playback(string path){
  //---------------------------

  this->playback.path = path;
  k4a_playback->start_thread(this);

  //---------------------------
}
void K4A_device::stop_threads(){
  //---------------------------

  this->k4a_capture->stop_thread();
  this->k4a_playback->stop_thread();

  //---------------------------
}
void K4A_device::reset_color_configuration(){
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
