#include "K4A_device.h"

#include <Engine/Engine.h>
#include <Engine/Capture/Kinect/Thread/K4A_capture.h>
#include <Engine/Capture/Kinect/Thread/K4A_replay.h>



//Constructor / Destructor
K4A_device::K4A_device(Engine* engine){
  //---------------------------

  eng::data::Node* eng_data = engine->get_eng_data();

  this->k4a_capture = new K4A_capture(engine);
  this->k4a_replay = new K4A_replay(engine);
  this->eng_scene = eng_data->get_eng_scene();

  //---------------------------
  this->init();
}
K4A_device::~K4A_device(){}

//Main function
void K4A_device::init(){
  //---------------------------

  //Device name
  string str_virtual = device.is_virtual ? "virtual_" : "";
  this->device.name = "kinect_" + str_virtual + to_string(device.index);

  //Device cloud
  this->object = new eng::structure::Object();
  object->name = device.name;

  //---------------------------
}
void K4A_device::draw_cloud(){
  //---------------------------

  eng_scene->insert_object_scene(object);

  //---------------------------
}
void K4A_device::run_capture(){
  //---------------------------

  if(!k4a_capture->is_thread_running()){
    k4a_capture->start_thread(this);
  }

  //---------------------------
}
void K4A_device::run_replay(string path){
  //---------------------------

  this->file.path = path;
  k4a_replay->start_thread(this);

  //---------------------------
}
void K4A_device::stop_threads(){
  //---------------------------

  this->k4a_capture->stop_thread();
  this->k4a_replay->stop_thread();

  //---------------------------
}
