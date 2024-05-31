#include "Sensor.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  dat::Node* node_data = node_engine->get_node_data();

  this->k4n_image = new k4n::processing::Image(node_k4n);
  this->k4n_config = new k4n::utils::Configuration();
  this->node_engine = node_engine;
  this->dat_graph = node_data->get_dat_graph();
  this->dat_entity = node_data->get_dat_entity();
  this->dat_set = node_data->get_data_set();
  this->dat_glyph = node_data->get_data_glyph();

  this->name = "k4n::sensor";
  this->entity_type = "k4n::device::Sensor";
  this->icon = ICON_FA_CAMERA_RETRO;

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::init(){
  //---------------------------

  //Profiler
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  this->profiler = new prf::graph::Profiler(name, "k4n::sensor");
  prf_manager->add_profiler(profiler);

  //Object
  object = dat::base::Object(node_engine);
  object.name = name;
  object.data.name = "sensor::object::data";
  object.data.topology.type = utl::topology::POINT;
  object.data.nb_data_max = 10000000;
  object.pose.model[2][3] = 1;
  dat_entity->init_entity(&object);

  this->start_thread();

  //---------------------------
}
void Sensor::reset(){
  //---------------------------

  object.reset();

  //---------------------------
}
void Sensor::update_pose(){
  //----------------------------

  //dat_entity->update_pose(&object);

  //----------------------------
}
void Sensor::remove(){
  if(profiler == nullptr) return;
  //---------------------------

  //Sensor related
  this->stop_thread();
  this->device.transformation.destroy();
  this->object.remove();

  //Profiler related
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf_manager->remove_profiler(profiler);
  this->profiler = nullptr;

  //---------------------------
}
void Sensor::visibility(bool value){
  //---------------------------

  this->is_visible = value;
  object.data.is_visible = value;
  object.visibility(value);

  //---------------------------
}
vec3 Sensor::convert_depth_2d_to_3d(ivec2 point_2d){
  //---------------------------

  uint16_t* buffer = reinterpret_cast<uint16_t*>(depth.data.buffer);
  int width = depth.data.width;

  //Retrieve image coordinates
  int x = point_2d[0];
  int y = point_2d[1];
  k4a_float2_t source_xy = { static_cast<float>(x), static_cast<float>(y) };
  float source_z = static_cast<float>(buffer[y * width + x]);

  //Convert it into 3D coordinate
  k4a_float3_t target_xyz;
  bool success = device.calibration.convert_2d_to_3d(source_xy, source_z, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &target_xyz);
  vec4 xyzw = vec4(target_xyz.xyz.x, target_xyz.xyz.y, target_xyz.xyz.z, 1);

  //Apply transformation
  float inv_scale = 1.0f / 1000.0f;
  xyzw.x = -xyzw.x * inv_scale;
  xyzw.y = -xyzw.y * inv_scale;
  xyzw.z = xyzw.z * inv_scale;
  vec3 pose = vec3(xyzw.z, xyzw.x, xyzw.y);

  //---------------------------
  return pose;
}

//Thread function
void Sensor::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread_running = true;
    this->thread = std::thread(&Sensor::run_thread, this);
  }

  //---------------------------
}
void Sensor::run_thread(){
  //---------------------------

  this->thread_init();

  //Sensor thread
  while(thread_running){
    this->thread_loop();
  }

  this->thread_end();

  //---------------------------
}
void Sensor::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Sensor::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_paused == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}



}
