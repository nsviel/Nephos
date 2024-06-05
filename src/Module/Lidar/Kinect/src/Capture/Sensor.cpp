#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, int index){
  //---------------------------

  this->gui_capture = new k4n::gui::Capture(node_k4n);
  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_image = new k4n::processing::Image(node_k4n);
  this->k4n_config = new k4n::utils::Configuration(node_k4n);

  this->device.idx_dev = index;
  this->name = "capture_" + to_string(index);
  this->data.topology.type = utl::topology::POINT;
  this->data.nb_data_max = 10000000;

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Sensor::info(){
  //---------------------------

  gui_capture->show_parameter(set_parent);

  //---------------------------
}
void Sensor::thread_init(){
  //---------------------------

  //Init elements
  this->device.idx_dev = 0;
  this->device.handle = k4a::device::open(device.idx_dev);
  if(!device.handle.is_valid()) return;

  this->device.serial_number = device.handle.get_serialnum();
  this->device.version = device.handle.get_version();

  //Configuration
  k4n_config->make_sensor_configuration(this);
  k4n_config->make_sensor_color_configuration(this);
  k4n_config->make_capture_calibration(this);
  k4n_config->make_transformation_from_calibration(this);
  this->device.handle.start_cameras(&device.configuration);

  //---------------------------
}
void Sensor::thread_loop(){
  prf::graph::Tasker* tasker = profiler.get_or_create_tasker("capture");
  //---------------------------

  tasker->loop_begin();

  //Next capture
  tasker->task_begin("capture");
  k4a::capture* capture = manage_new_capture();
  if(capture == nullptr) return;
  tasker->task_end("capture");

  //Wait previous threads to finish
  tasker->task_begin("wait");
  this->manage_old_capture(capture);
  tasker->task_end("wait");

  //Run processing
  k4n_image->start_thread(this);

  //Loop sleeping
  tasker->task_begin("pause");
  this->manage_pause();
  tasker->task_end("pause");

  tasker->loop_end();

  //---------------------------
}
void Sensor::thread_end(){
  //---------------------------

  this->device.handle.close();

  //---------------------------
}

//Subfunction
k4a::capture* Sensor::manage_new_capture(){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool ok = device.handle.get_capture(capture, std::chrono::milliseconds(2000));
  if(!capture->is_valid()){
    delete capture;
    return nullptr;
  }

  //---------------------------
  return capture;
}
void Sensor::manage_old_capture(k4a::capture* capture){
  static std::queue<k4a::capture*> capture_queue;
  //---------------------------

  // Add the new capture to the queue
  capture_queue.push(capture);

  // Check if the queue size exceeds 5
  k4n_image->wait_thread();
  if(capture_queue.size() > 5){
    // Delete the oldest capture
    delete capture_queue.front();
    capture_queue.pop();
  }

  // Update the sensor parameter
  this->device.capture = capture;

  //---------------------------
}
void Sensor::manage_pause(){
  /*dyn::base::Player* player = &set_parent->player;
  //---------------------------

  //If pause, wait until end pause or end thread
  if(player->pause || !player->play){
    this->profiler.reset();
    while(player->pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }
*/
  //---------------------------
}
void Sensor::manage_reset(){
  //---------------------------

  //this->reset();
  //this->run_thread();

  //---------------------------
}
void Sensor::manage_configuration(){
  //---------------------------

  k4n_config->make_sensor_color_configuration(this);
  this->color.config = k4n_struct->config.color;
  this->depth.config = k4n_struct->config.depth;
  this->ir.config = k4n_struct->config.ir;

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

}
