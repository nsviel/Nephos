#include "Operation.h"

#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <Operation/Namespace.h>
#include <Kinect/Namespace.h>
#include <Engine/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Operation::Operation(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();

  this->ope_voxelizer = new ope::Voxelizer();
  this->ope_trianguler = new ope::Triangulation();
  this->ope_colorizer = new ope::color::Colorizer();
  this->ope_normal = new ope::normal::KNN();

  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::start_thread(k4n::dev::Sensor* sensor){
  if(sensor->profiler == nullptr) return;
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Operation::run_thread(k4n::dev::Sensor* sensor){
  k4n::dev::Master* master = sensor->master;
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("processing");
  //---------------------------

  tasker->loop_begin();

  //Colorizer
  tasker->task_begin("colorization");
  this->colorize_object(sensor);
  tasker->task_end("colorization");

  //Update object data
  tasker->task_begin("update");
  this->update_object(sensor);
  tasker->task_end("update");

  tasker->loop_end();

  //---------------------------
  this->idle = true;
}
void Operation::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }


  //---------------------------
}

//Subfunction
void Operation::colorize_object(k4n::dev::Sensor* sensor){
  //---------------------------

  ope::color::Configuration config;
  config.color_mode = sensor->master->operation.color_mode;
  config.heatmap_mode = sensor->master->operation.heatmap_mode;
  config.intensity_diviser = sensor->master->operation.intensity_diviser;
  config.heatmap_range_height = sensor->master->operation.range_height;
  config.unicolor = sensor->master->operation.unicolor;

  ope_colorizer->make_colorization(sensor, config);

  //---------------------------
}
void Operation::update_object(k4n::dev::Sensor* sensor){
  //---------------------------

  dat::base::Object* object = sensor->get_object();
  object->update_data();
  object->update_glyph();

  //---------------------------
}

}
