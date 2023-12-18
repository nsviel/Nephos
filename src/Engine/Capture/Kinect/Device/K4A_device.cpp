#include "K4A_device.h"

#include <Engine/Engine.h>
#include <Engine/Capture/Kinect/Thread/K4A_capture.h>
#include <Engine/Capture/Kinect/Thread/K4A_playback.h>



//Constructor / Destructor
K4A_device::K4A_device(Engine* engine){
  //---------------------------

  eng::data::Node* eng_data = engine->get_eng_data();

  this->k4a_capture = new K4A_capture(engine);
  this->k4a_playback = new K4A_playback(engine);
  this->eng_scene = eng_data->get_eng_scene();
  this->eng_glyph = eng_data->get_eng_glyph();

  //---------------------------
}
K4A_device::~K4A_device(){}

//Main function
void K4A_device::init(){
  //---------------------------

  //Device name
  string str_mode = device.is_virtual ? "playback_" : "capture_";
  this->device.name = str_mode + to_string(device.index);

  //Device cloud
  cloud.object = new eng::structure::Cloud();
  cloud.object->name = device.name;
  cloud.object->draw_type_name = "point";
  eng_glyph->create_cloud_glyphs(cloud.object);
  eng_scene->insert_object_scene(cloud.object);

  //---------------------------
}
void K4A_device::destroy(){
  //---------------------------

  this->device.transformation.destroy();

  //---------------------------
}
void K4A_device::draw_cloud(){
  //---------------------------

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
void K4A_device::run_replay(string path){
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
