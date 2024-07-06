#include "Data.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  dyn::Node* node_dynamic = node_engine->get_node_dynamic();
  dat::Node* node_data = node_k4n->get_node_data();

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_operation = new k4n::processing::Operation(node_k4n);
  this->k4n_format = new k4n::processing::image::Format(node_k4n);
  this->dat_image = node_data->get_dat_image();
  this->k4n_transformation = new k4n::processing::image::Transformation(node_k4n);
  this->k4n_color = new k4n::processing::image::Color(node_k4n);
  this->k4n_depth = new k4n::processing::image::Depth(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::find_data_from_capture(k4n::structure::Sensor* sensor){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("kinect::data");
  //---------------------------

  tasker->loop();

  //Depth data
  tasker->task_begin("depth");
  k4n_depth->find_data_depth(sensor);
  tasker->task_end("depth");

  //Color data
  tasker->task_begin("color");
  k4n_color->find_data_color(sensor);
  tasker->task_end("color");

  //Infrared data
  tasker->task_begin("infrared");
  this->find_data_ir(sensor);
  tasker->task_end("infrared");

  //Cloud data
  tasker->task_begin("transformation");
  this->find_data_cloud(sensor);
  tasker->task_end("transformation");

  //---------------------------
}

//Subfunction
void Data::find_data_ir(k4n::structure::Sensor* sensor){
  //---------------------------

  //Get k4a image
  k4a::image ir = sensor->device.capture->get_ir_image();
  if(!ir.is_valid()) return;

  //Data
  sensor->ir.data.name = "ir";
  sensor->ir.data.k4a_image = ir;
  sensor->ir.data.width = ir.get_width_pixels();
  sensor->ir.data.height = ir.get_height_pixels();
  sensor->ir.data.buffer = ir.get_buffer();
  sensor->ir.data.size = ir.get_size();
  sensor->ir.data.format = k4n_format->retrieve_format_from_k4a(ir.get_format());
  sensor->ir.data.timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);
  k4n_operation->convert_uint8_to_vec_uint16(sensor->ir.data.buffer, sensor->ir.data.size, sensor->buffer_ir);

  //Image
  k4n_operation->convert_ir_into_color(sensor);
  sensor->ir.image.name = "Infrared";
  sensor->ir.image.size = sensor->ir.image.data.size();
  sensor->ir.image.width = sensor->ir.data.width;
  sensor->ir.image.height = sensor->ir.data.height;
  sensor->ir.image.format = "R8G8B8A8_SRGB";
  sensor->ir.image.type = utl::media::INTENSITY;
  sensor->ir.image.timestamp = sensor->ir.data.timestamp;
  dat_image->add_image(sensor, &sensor->ir.image);

  //---------------------------
}
void Data::find_data_cloud(k4n::structure::Sensor* sensor){
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
