#include "Device.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Device::Device(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  dat::Node* node_data = node_engine->get_node_data();

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->node_engine = node_engine;
  this->dat_graph = node_data->get_data_graph();
  this->dat_entity = node_data->get_data_entity();
  this->dat_set = node_data->get_data_set();
  this->dat_glyph = node_data->get_data_glyph();
  this->k4n_capture = new k4n::capture::Sensor(node_k4n);
  this->k4n_playback = new k4n::playback::Sensor(node_k4n);
  this->gui_sensor = new k4n::gui::Sensor(node_k4n);

  this->entity_type = "k4n::device::Sensor";
  this->icon = ICON_FA_CAMERA_RETRO;

  //---------------------------
}
Device::~Device(){}

//Main function
void Device::init(){
  //---------------------------

  //Sensor name
  string str_mode = (master->mode == k4n::dev::PLAYBACK) ? "playback_" : "capture_";
  this->param.name = str_mode + to_string(param.index);

  //Sensor profiler
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  this->profiler = new prf::graph::Profiler(param.name, "k4n::sensor");
  prf_manager->add_profiler(profiler);

  //Sensor cloud
  object = dat::base::Object(node_engine);
  object.name = param.name;
  object.data.name = "sensor::object::data";
  object.data.topology.type = utl::topology::POINT;
  object.data.nb_data_max = 10000000;
  object.pose.model[2][3] = 1;
  dat_entity->init_entity(&object);

  image.color.name = "Color";
  dat_graph->assign_UID(&image.color);
  image.ir.name = "IR";
  dat_graph->assign_UID(&image.ir);
  image.depth.name = "Depth";
  dat_graph->assign_UID(&image.depth);

  //---------------------------
}
void Device::reset(){
  //---------------------------

  object.reset_entity();

  //---------------------------
}
void Device::info(){
  //---------------------------

  gui_sensor->show_sensor(this);

  //---------------------------
}

//Entity function
void Device::update_pose(){
  //----------------------------

  object.update_pose();

  //----------------------------
}
void Device::remove_entity(){
  if(profiler == nullptr) return;
  //---------------------------

  this->stop_threads();

  //Remove tasker
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf_manager->remove_profiler(profiler);
  this->profiler = nullptr;

  //Remove sensor elements
  this->param.transformation.destroy();
  this->object.remove_entity();

  //Supress this sensor from lists
  k4n_struct->list_sensor.remove(this);

  //---------------------------
}
void Device::set_visibility(bool value){
  //---------------------------

  this->is_visible = value;
  object.data.is_visible = value;
  object.set_visibility(value);

  //---------------------------
}

//Thread function
void Device::start_thread(){
  if(sensor == nullptr) return;
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Device::run_thread, this, sensor);
  }

  //---------------------------
  this->thread_running = true;
  this->thread_idle = false;
}
void Device::run_thread(){
  //---------------------------

  this->thread_init(sensor);

  //Device thread
  while(thread_running){
    this->thread_loop(sensor);
  }

  this->thread_end(sensor);

  //---------------------------
  this->thread_idle = true;
}
void Device::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Device::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_paused == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}


//Capture function
void Device::run_thread_capture(){
  //---------------------------

  this->stop_threads();
  //k4n_capture->start_thread();
  this->thread_running = true;
  this->object.set_visibility(true);

  //---------------------------
}
void Device::run_thread_playback(string path){
  //---------------------------

  this->stop_threads();
  this->param.path.data = path;
  k4n_playback->start_thread();
  this->thread_running = true;
  this->object.set_visibility(true);

  //---------------------------
}
void Device::stop_threads(){
  //---------------------------

  //this->k4n_capture->stop_thread();
  this->k4n_playback->stop_thread();
  this->thread_running = false;
  this->object.clear_data();
  this->object.set_visibility(false);

  //---------------------------
}
void Device::wait_threads(){
  //---------------------------

  //Capture
  /*if(k4n_capture->is_thread_running()){
    k4n_capture->wait_thread();
  }
  //Playback
  else if(k4n_playback->is_thread_running()){
    k4n_playback->wait_thread();
  }
*/
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
