#include "Thread.h"

#include <Kinect/Namespace.h>
#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Thread::Thread(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  dyn::Node* node_dynamic = node_engine->get_node_dynamic();

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_cloud = new k4n::processing::Cloud(node_k4n);
  this->thread_pool = node_engine->get_thread_pool();
  this->dyn_operation = node_dynamic->get_ope_image();
  this->k4n_transformation = new k4n::processing::image::Transformation(node_k4n);
  this->k4n_color = new k4n::processing::image::Color(node_k4n);
  this->k4n_depth = new k4n::processing::image::Depth(node_k4n);
  this->k4n_ir = new k4n::processing::image::Infrared(node_k4n);

  //---------------------------
}
Thread::~Thread(){}

//Main function
void Thread::start_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Thread::run_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  //Retrieve data from capture
  this->find_data_from_capture(sensor);

  //Convert data into cloud
  k4n_cloud->start_thread(sensor);

  //Dynamic operation
  dyn_operation->start_thread(sensor);

  //---------------------------
  this->thread_idle = true;
}
void Thread::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  k4n_cloud->wait_thread();
  dyn_operation->wait_thread();

  //---------------------------
}

//Subfunction
void Thread::find_data_from_capture(k4n::structure::Sensor* sensor){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("kinect::data");
  //---------------------------

  tasker->loop();

  //Depth data
  tasker->task_begin("depth");
  k4n_depth->extract_data(sensor);
  tasker->task_end("depth");

  //Color data
  tasker->task_begin("color");
  k4n_color->extract_data(sensor);
  tasker->task_end("color");

  //Infrared data
  tasker->task_begin("infrared");
  k4n_ir->extract_data(sensor);
  tasker->task_end("infrared");

  //Cloud data
  tasker->task_begin("transformation");
  this->find_data_cloud(sensor);
  tasker->task_end("transformation");

  //---------------------------
}
void Thread::find_data_cloud(k4n::structure::Sensor* sensor){
  sensor->color.cloud = {};
  sensor->ir.cloud = {};
  sensor->depth.cloud = {};
  //---------------------------

  switch(k4n_struct->config.depth.transformation_mode){
    case k4n::depth::DEPTH_TO_COLOR:{
      k4n_transformation->find_depth_and_ir_to_color(sensor);
      sensor->color.cloud = sensor->color.data;
      sensor->depth.cloud.calibration_type = K4A_CALIBRATION_TYPE_COLOR;
      break;
    }
    case k4n::depth::COLOR_TO_DEPTH:{
      k4n_transformation->find_color_to_depth(sensor);
      sensor->depth.cloud = sensor->depth.data;
      sensor->ir.cloud = sensor->ir.data;
      sensor->depth.cloud.calibration_type = K4A_CALIBRATION_TYPE_DEPTH;
      break;
    }
  }

  //---------------------------
}

}
