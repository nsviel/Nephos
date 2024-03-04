#include "Sensor.h"

#include <Engine/Namespace.h>
#include <K4N/Namespace.h>
#include <Scene/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Sensor::Sensor(k4n::structure::Struct_k4n* struct_k4n){
  //---------------------------

  eng::scene::Node* node_scene = struct_k4n->node_scene;

  this->node_engine = struct_k4n->node_engine;
  this->sce_entity = node_scene->get_scene_entity();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->k4n_capture = new k4n::thread::Capture();
  this->k4n_playback = new k4n::thread::Playback();

  this->entity_type = "k4n::device::Sensor";
  this->icon = ICON_FA_CAMERA_RETRO;

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  this->remove_entity();

  delete k4n_capture;
  delete k4n_playback;

  //---------------------------
}

//Main function
void Sensor::init(){
  //---------------------------

  //Sensor name
  string str_mode = (param.mode == k4n::mode::PLAYBACK) ? "playback_" : "capture_";
  this->param.name = str_mode + to_string(param.index);

  //Sensor profiler
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  this->profiler = new prf::graph::Profiler(param.name, "k4n::sensor");
  this->profiler->new_tasker("capture");
  this->profiler->new_tasker("data");
  this->profiler->new_tasker("cloud");
  this->profiler->new_tasker("image");
  this->profiler->new_tasker("processing");
  prf_manager->add_profiler(profiler);

  //Sensor cloud
  object = utl::entity::Object(node_engine);
  object.name = param.name;
  object.data->draw_type = utl::topology::POINT;
  object.data->nb_data_max = 10000000;
  sce_entity->init_entity(&object);

  //---------------------------
}
void Sensor::reset(){
  //---------------------------

  object.reset_entity();

  //---------------------------
}

//Entity function
void Sensor::update_pose(){
  //----------------------------

  //Retrieve capture data
  //std::unique_lock<std::mutex> lock(object.data->mutex);
  //object.update_data();
  object.update_pose();

  //----------------------------
}
void Sensor::remove_entity(){
  //---------------------------

  //Remove sensor elements
  this->stop_threads();
  this->param.transformation.destroy();
  this->object.remove_entity();
  this->master->manage_suppression(this);

  //Remove tasker
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf_manager->remove_profiler(profiler);

  //---------------------------
}
void Sensor::set_visibility(bool value){
  //---------------------------

  this->is_visible = value;
  object.data->is_visible = value;
  object.set_visibility(value);

  //---------------------------
}
void Sensor::reset_entity(){
  //---------------------------

  object.reset_entity();

  //---------------------------
}

//Capture function
void Sensor::run_capture(){
  //---------------------------

  this->stop_threads();
  k4n_capture->start_thread(this);

  //---------------------------
}
void Sensor::run_playback(string path){
  //---------------------------

  this->stop_threads();
  this->param.path.data = path;
  k4n_playback->start_thread(this);

  //---------------------------
}
void Sensor::stop_threads(){
  //---------------------------

  this->k4n_capture->stop_thread();
  this->k4n_playback->stop_thread();

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
