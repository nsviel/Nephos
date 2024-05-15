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

  this->k4n_data = new k4n::processing::Data(node_k4n);
  this->k4n_config = new k4n::utils::Configuration();
  this->node_engine = node_engine;
  this->dat_graph = node_data->get_data_graph();
  this->dat_entity = node_data->get_data_entity();
  this->dat_set = node_data->get_data_set();
  this->dat_glyph = node_data->get_data_glyph();
  this->gui_sensor = new k4n::gui::Sensor(node_k4n);

  this->name = "k4n::sensor";
  this->entity_type = "k4n::device::Sensor";
  this->icon = ICON_FA_CAMERA_RETRO;

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::init(){
  //---------------------------

  this->init_profiler();
  this->init_object();
  this->init_image();

  //---------------------------
}
void Sensor::reset(){
  //---------------------------

  object.reset();

  //---------------------------
}
void Sensor::info(){
  //---------------------------

  gui_sensor->show_sensor(this);

  //---------------------------
}
void Sensor::update_pose(){
  //----------------------------

  object.update_pose();

  //----------------------------
}
void Sensor::remove(){
  if(profiler == nullptr) return;
  //---------------------------

  //Sensor related
  this->stop_thread();
  this->param.transformation.destroy();
  this->object.remove();

  //Profiler related
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf_manager->remove_profiler(profiler);
  this->profiler = nullptr;

  //---------------------------
}
void Sensor::set_visibility(bool value){
  //---------------------------

  this->is_visible = value;
  object.data.is_visible = value;
  object.set_visibility(value);

  //---------------------------
}

//Init function
void Sensor::init_profiler(){
  //---------------------------

  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  this->profiler = new prf::graph::Profiler(param.name, "k4n::sensor");
  prf_manager->add_profiler(profiler);

  //---------------------------
}
void Sensor::init_object(){
  //---------------------------

  //Object
  object = dat::base::Object(node_engine);
  object.name = param.name;
  object.data.name = "sensor::object::data";
  object.data.topology.type = utl::topology::POINT;
  object.data.nb_data_max = 10000000;
  object.pose.model[2][3] = 1;
  dat_entity->init_entity(&object);

  //Transformation
  glm::mat4 mat = utl::transformation::find_transformation_from_file(param.path.transformation);
  pose.model = mat;
  pose.model_init = mat;

  //---------------------------
}
void Sensor::init_image(){
  //---------------------------

  image.color.name = "Color";
  dat_graph->assign_UID(&image.color);

  image.ir.name = "IR";
  dat_graph->assign_UID(&image.ir);

  image.depth.name = "Depth";
  dat_graph->assign_UID(&image.depth);

  //---------------------------
}

//Thread function
void Sensor::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Sensor::run_thread, this);
  }

  //---------------------------
  this->thread_running = true;
  this->thread_idle = false;
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
  this->thread_idle = true;
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
