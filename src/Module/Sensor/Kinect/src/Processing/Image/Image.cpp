#include "Image.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Image::Image(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  dyn::Node* node_dynamic = node_engine->get_node_dynamic();
  dat::Node* node_data = node_k4n->get_node_data();

  this->tj_handle = tjInitDecompress();
  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_operation = new k4n::processing::Operation(node_k4n);
  this->k4n_cloud = new k4n::processing::Cloud(node_k4n);
  this->thread_pool = node_engine->get_thread_pool();
  this->dyn_operation = node_dynamic->get_ope_image();
  this->dat_image = node_data->get_dat_image();
  this->k4n_transformation = new k4n::processing::image::Transformation(node_k4n);

  //---------------------------
}
Image::~Image(){
  //---------------------------

  tjDestroy(tj_handle);

  //---------------------------
}

//Main function
void Image::start_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Image::run_thread(k4n::structure::Sensor* sensor){
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
void Image::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  k4n_cloud->wait_thread();
  dyn_operation->wait_thread();

  //---------------------------
}

//Data function
void Image::find_data_from_capture(k4n::structure::Sensor* sensor){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("kinect::data");
  //---------------------------

  tasker->loop();

  //Depth data
  tasker->task_begin("depth");
  this->find_data_depth(sensor);
  tasker->task_end("depth");

  //Color data
  tasker->task_begin("color");
  this->find_data_color(sensor);
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
void Image::find_data_depth(k4n::structure::Sensor* sensor){
  //---------------------------

  //Get k4a image
  k4a::image depth = sensor->device.capture->get_depth_image();
  if(!depth.is_valid()) return;

  //Data
  sensor->depth.data.name = "depth";
  sensor->depth.data.k4a_image = depth;
  sensor->depth.data.width = depth.get_width_pixels();
  sensor->depth.data.height = depth.get_height_pixels();
  sensor->depth.data.buffer = depth.get_buffer();
  sensor->depth.data.size = depth.get_size();
  sensor->depth.data.format = retrieve_format_from_k4a(depth.get_format());
  sensor->depth.data.temperature = sensor->device.capture->get_temperature_c();
  sensor->depth.data.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  k4n_operation->convert_uint8_to_vec_uint16(sensor->depth.data.buffer, sensor->depth.data.size, sensor->buffer_depth);

  //Image
  k4n_operation->convert_depth_into_color(sensor);
  sensor->depth.image.name = "Depth";
  sensor->depth.image.size = sensor->depth.image.data.size();
  sensor->depth.image.width = sensor->depth.data.width;
  sensor->depth.image.height = sensor->depth.data.height;
  sensor->depth.image.format = "R8G8B8A8_SRGB";
  sensor->depth.image.type = utl::media::DEPTH;
  sensor->depth.image.timestamp = sensor->depth.data.timestamp;
  dat_image->add_image(sensor, &sensor->depth.image);

  //---------------------------
}
void Image::find_data_color(k4n::structure::Sensor* sensor){
  //---------------------------

  //Get k4a image
  k4a::image color = sensor->device.capture->get_color_image();
  if(!color.is_valid()) return;

  //Data
  sensor->color.data.name = "color";
  sensor->color.data.k4a_image = color;
  sensor->color.data.size = color.get_size();
  sensor->color.data.width = color.get_width_pixels();
  sensor->color.data.height = color.get_height_pixels();
  sensor->color.data.buffer = color.get_buffer();
  sensor->color.data.format = retrieve_format_from_k4a(color.get_format());
  sensor->color.data.timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);

  //Image
  sensor->color.image.name = "Color";
  sensor->color.image.data = std::vector<uint8_t>(sensor->color.data.buffer, sensor->color.data.buffer + sensor->color.data.size);
  sensor->color.image.size = sensor->color.image.data.size();
  sensor->color.image.width = sensor->color.data.width;
  sensor->color.image.height = sensor->color.data.height;
  sensor->color.image.format = sensor->color.data.format;
  sensor->color.image.type = utl::media::COLOR;
  sensor->color.image.timestamp = sensor->color.data.timestamp;
  dat_image->add_image(sensor, &sensor->color.image);

  //Current timestamp
  sensor->timestamp.current = sensor->color.data.timestamp;

  //---------------------------
}
void Image::find_data_ir(k4n::structure::Sensor* sensor){
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
  sensor->ir.data.format = retrieve_format_from_k4a(ir.get_format());
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
void Image::find_data_cloud(k4n::structure::Sensor* sensor){
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

//Subfunction
std::string Image::retrieve_format_from_k4a(k4a_image_format_t color_format){
  std::string format = "";
  //---------------------------

  if(color_format == K4A_IMAGE_FORMAT_COLOR_MJPG){
    format = "MJPEG";
  }else if(color_format == K4A_IMAGE_FORMAT_COLOR_NV12){
    format = "NV12";
  }else if(color_format == K4A_IMAGE_FORMAT_COLOR_YUY2){
    format = "YUY2";
  }else if(color_format == K4A_IMAGE_FORMAT_COLOR_BGRA32){
    format = "B8G8R8A8_SRGB";
  }else if(color_format == K4A_IMAGE_FORMAT_DEPTH16){
    format = "DEPTH16";
  }else if(color_format == K4A_IMAGE_FORMAT_IR16){
    format = "IR16";
  }else if(color_format == K4A_IMAGE_FORMAT_CUSTOM8){
    format = "CUSTOM8";
  }else if(color_format == K4A_IMAGE_FORMAT_CUSTOM16){
    format = "CUSTOM16";
  }else if(color_format == K4A_IMAGE_FORMAT_CUSTOM){
    format = "CUSTOM";
  }

  //---------------------------
  return format;
}
void Image::retrieve_data_from_capture(k4a::image& image, std::vector<uint8_t>& data, std::string& format){
  //---------------------------

  if(format == "MJPEG"){
    this->retrieve_bgra_from_mjpeg(image, data);
    format = "B8G8R8A8_SRGB";
  }else{
    uint8_t* image_data = image.get_buffer();
    size_t size = image.get_size();
    data = std::vector<uint8_t>(image_data, image_data + size);
    format = "B8G8R8A8_SRGB";
  }

  //---------------------------
}
void Image::retrieve_bgra_from_mjpeg(k4a::image& image, std::vector<uint8_t>& data){
  //---------------------------

  int width = image.get_width_pixels();
  int height = image.get_height_pixels();
  int size = image.get_size();
  uint8_t* mpeg = image.get_buffer();
  std::vector<uint8_t> bgra(width * height * tjPixelSize[TJPF_RGBA]);
  int flags = TJFLAG_FASTDCT | TJFLAG_FASTUPSAMPLE;

  int ret = tjDecompress2(tj_handle, &mpeg[0], size, bgra.data(), width, 0, height, TJPF_RGBA, flags);
  if(ret != 0){
    std::cout<<"[error] MPEG convertion error"<<std::endl;
  }
  data = bgra;

  //Creat a new k4a image with RGBA data format
  image = k4a::image::create_from_buffer(K4A_IMAGE_FORMAT_COLOR_BGRA32, width, height, width * 4, data.data(), data.size(), nullptr, nullptr);

  //---------------------------
}


}
