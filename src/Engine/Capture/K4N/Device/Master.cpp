#include "Master.h"

#include <Engine/Engine.h>


namespace k4n::dev{


//Constructor / Destructor
Master::Master(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->type = "Master";

  //---------------------------
}
Master::~Master(){}

//Main function


//Entity function
void Master::update_entity(){
  eng::camera::Node* node_camera = engine->get_node_camera();
  eng::camera::Control* cam_control = node_camera->get_camera_control();
  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  //----------------------------

  for(int i=0; i<list_device.size(); i++){
    k4n::dev::Sensor* device = *next(list_device.begin(), i);
    cam_control->compute_camera_mvp(device->cloud.object->data);
    sce_glyph->update_glyph_object(device->cloud.object);
  }

  //----------------------------
}
void Master::remove_entity(){
  eng::capture::Node* node_capture = engine->get_node_capture();
  k4n::Node* node_kinect = node_capture->get_node_kinect();
  k4n::dev::Swarm* k4a_swarm = node_kinect->get_k4a_swarm();
  //---------------------------

  for(int i=0; i<list_device.size(); i++){
    k4n::dev::Sensor* device = *next(list_device.begin(), i);
    //k4a_swarm->close_device(device);
  }

  //---------------------------
}
void Master::visibility_entity(bool value){
  //---------------------------

  this->is_visible = value;

  for(int i=0; i<list_device.size(); i++){
    k4n::dev::Sensor* device = *next(list_device.begin(), i);
    device->cloud.object->visibility_entity(value);
  }

  //---------------------------
}
void Master::reset_entity(){
  //---------------------------

  for(int i=0; i<list_device.size(); i++){
    k4n::dev::Sensor* device = *next(list_device.begin(), i);
    device->cloud.object->reset_entity();
    device->player.ts_seek = device->player.ts_beg;
  }

  //---------------------------
}

}
