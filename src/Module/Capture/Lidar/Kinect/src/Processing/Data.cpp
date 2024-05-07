#include "Data.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();

  this->tj_handle = tjInitDecompress();
  this->k4n_cloud = new k4n::processing::Cloud(node_k4n);
  this->k4n_image = new k4n::processing::Image(node_k4n);
  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Data::~Data(){
  //---------------------------

  tjDestroy(tj_handle);

  //---------------------------
}

//Main function
void Data::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Data::run_thread(k4n::dev::Sensor* sensor){
  if(sensor->profiler == nullptr) return;
  //---------------------------

  //Retrieve data from capture
  this->find_data_from_capture(sensor);

  //Convert data into cloud
  k4n_cloud->start_thread(sensor);

  //Encode image as texture
  k4n_image->start_thread(sensor);

  //---------------------------
  this->idle = true;
}
void Data::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  k4n_image->wait_thread();
  k4n_cloud->wait_thread();

  //---------------------------
}

//Data function
void Data::find_data_from_capture(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("data");
  //---------------------------

  tasker->loop_begin();

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

  tasker->loop_end();

  //End
  float fps = tasker->get_loop_fps();
  sensor->color.data.fps = fps;
  sensor->depth.data.fps = fps;
  sensor->ir.data.fps = fps;
  float& ts_cur = sensor->master->player->get_ts_cur();
  ts_cur = sensor->color.data.timestamp;
  sensor->param.data_ready = true;

  //---------------------------
}
void Data::find_data_depth(k4n::dev::Sensor* sensor){
  //---------------------------

  //Get k4a image
  k4a::image depth = sensor->param.capture->get_depth_image();
  if(!depth.is_valid()) return;

  //Data
  sensor->depth.data.name = "depth";
  sensor->depth.data.k4a_image = depth;
  sensor->depth.data.width = depth.get_width_pixels();
  sensor->depth.data.height = depth.get_height_pixels();
  sensor->depth.data.buffer = depth.get_buffer();
  sensor->depth.data.size = depth.get_size();
  sensor->depth.data.format = retrieve_format_from_k4a(depth.get_format());
  sensor->depth.data.temperature = sensor->param.capture->get_temperature_c();
  sensor->depth.data.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
}
void Data::find_data_color(k4n::dev::Sensor* sensor){
  //---------------------------

  //Get k4a image
  k4a::image color = sensor->param.capture->get_color_image();
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

  //---------------------------
}
void Data::find_data_ir(k4n::dev::Sensor* sensor){
  //---------------------------

  //Get k4a image
  k4a::image ir = sensor->param.capture->get_ir_image();
  if(!ir.is_valid()) return;

  //Data
  sensor->ir.data.name = "ir";
  sensor->ir.data.k4a_image = ir;
  sensor->ir.data.width = ir.get_width_pixels();
  sensor->ir.data.height = ir.get_height_pixels();
  sensor->ir.data.buffer = ir.get_buffer();
  sensor->ir.data.buffer = ir.get_buffer();
  sensor->ir.data.size = ir.get_size();
  sensor->ir.data.format = retrieve_format_from_k4a(ir.get_format());
  sensor->ir.data.timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
}

//Transformed data
void Data::find_data_cloud(k4n::dev::Sensor* sensor){
  sensor->color.cloud = {};
  sensor->ir.cloud = {};
  sensor->depth.cloud = {};
  //---------------------------

  switch(sensor->master->operation.transformation_mode){
    case k4n::transformation::DEPTH_TO_COLOR:{
      this->find_depth_and_ir_to_color(sensor);
      sensor->color.cloud = sensor->color.data;
      sensor->depth.cloud.calibration_type = K4A_CALIBRATION_TYPE_COLOR;
      break;
    }
    case k4n::transformation::COLOR_TO_DEPTH:{
      this->find_color_to_depth(sensor);
      sensor->depth.cloud = sensor->depth.data;
      sensor->ir.cloud = sensor->ir.data;
      sensor->depth.cloud.calibration_type = K4A_CALIBRATION_TYPE_DEPTH;
      break;
    }
  }

  //---------------------------
}
void Data::find_depth_to_color(k4n::dev::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image depth_transformed = k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16,
    sensor->param.calibration.color_camera_calibration.resolution_width,
    sensor->param.calibration.color_camera_calibration.resolution_height,
    sensor->param.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  sensor->param.transformation.depth_image_to_color_camera(sensor->depth.data.k4a_image, &depth_transformed);
  if(!depth_transformed.is_valid()) return;

  //Data
  sensor->depth.cloud.name = "depth_to_color";
  sensor->depth.cloud.k4a_image = depth_transformed;
  sensor->depth.cloud.size = depth_transformed.get_size();
  sensor->depth.cloud.width = depth_transformed.get_width_pixels();
  sensor->depth.cloud.height = depth_transformed.get_height_pixels();
  sensor->depth.cloud.buffer = depth_transformed.get_buffer();
  sensor->depth.cloud.format = sensor->depth.data.format;

  //---------------------------
}
void Data::find_depth_and_ir_to_color(k4n::dev::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  //Depth images
  k4a::image depth_transformed = k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16,
    sensor->param.calibration.color_camera_calibration.resolution_width,
    sensor->param.calibration.color_camera_calibration.resolution_height,
    sensor->param.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  //IR images
  k4a::image ir = k4a::image::create_from_buffer(
    K4A_IMAGE_FORMAT_CUSTOM16,
    sensor->ir.data.width,
    sensor->ir.data.height,
    sensor->ir.data.width * static_cast<int>(sizeof(uint16_t)),
    sensor->ir.data.buffer,
    sensor->ir.data.size,
    nullptr,
    nullptr);
  k4a::image ir_transformed = k4a::image::create(
    K4A_IMAGE_FORMAT_CUSTOM16,
    sensor->param.calibration.color_camera_calibration.resolution_width,
    sensor->param.calibration.color_camera_calibration.resolution_height,
    sensor->param.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  uint32_t value_no_data = 0;
  sensor->param.transformation.depth_image_to_color_camera_custom(sensor->depth.data.k4a_image, ir, &depth_transformed, &ir_transformed, K4A_TRANSFORMATION_INTERPOLATION_TYPE_LINEAR, value_no_data);
  if(!depth_transformed.is_valid()) return;

  //Depth transformed
  sensor->depth.cloud.name = "depth_to_color";
  sensor->depth.cloud.k4a_image = depth_transformed;
  sensor->depth.cloud.size = depth_transformed.get_size();
  sensor->depth.cloud.width = depth_transformed.get_width_pixels();
  sensor->depth.cloud.height = depth_transformed.get_height_pixels();
  sensor->depth.cloud.buffer = depth_transformed.get_buffer();
  sensor->depth.cloud.format = sensor->depth.data.format;

  //IR transformed
  sensor->ir.cloud.name = "ir_to_color";
  sensor->ir.cloud.k4a_image = ir_transformed;
  sensor->ir.cloud.size = ir_transformed.get_size();
  sensor->ir.cloud.width = ir_transformed.get_width_pixels();
  sensor->ir.cloud.height = ir_transformed.get_height_pixels();
  sensor->ir.cloud.buffer = ir_transformed.get_buffer();
  sensor->ir.cloud.format = sensor->ir.data.format;

  //---------------------------
}
void Data::find_ir_to_color(k4n::dev::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->ir.data.k4a_image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image ir_transformed = k4a::image::create(
    K4A_IMAGE_FORMAT_DEPTH16,
    sensor->param.calibration.color_camera_calibration.resolution_width,
    sensor->param.calibration.color_camera_calibration.resolution_height,
    sensor->param.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  k4a::image ir = k4a::image::create_from_buffer(
    K4A_IMAGE_FORMAT_DEPTH16,
    sensor->ir.data.width,
    sensor->ir.data.height,
    sensor->ir.data.width * static_cast<int>(sizeof(uint16_t)),
    sensor->ir.data.buffer,
    sensor->ir.data.size,
    nullptr,
    nullptr);

  sensor->param.transformation.depth_image_to_color_camera(ir, &ir_transformed);
  if(!ir_transformed.is_valid()) return;

  //Data
  sensor->ir.cloud.name = "depth_to_color";
  sensor->ir.cloud.k4a_image = ir_transformed;
  sensor->ir.cloud.size = ir_transformed.get_size();
  sensor->ir.cloud.width = ir_transformed.get_width_pixels();
  sensor->ir.cloud.height = ir_transformed.get_height_pixels();
  sensor->ir.cloud.buffer = ir_transformed.get_buffer();
  sensor->ir.cloud.format = sensor->ir.data.format;

  //---------------------------
}
void Data::find_color_to_depth(k4n::dev::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  if(sensor->color.data.format == "YUY2"){
    sensor->color.data.k4a_image = k4a::image::create_from_buffer(
      K4A_IMAGE_FORMAT_COLOR_BGRA32,
      sensor->ir.data.width,
      sensor->ir.data.height,
      sensor->ir.data.width * static_cast<int>(sizeof(uint32_t)),
      retrieve_bgra_from_yuy2(sensor->color.data.buffer, sensor->ir.data.width, sensor->ir.data.height),
      sensor->ir.data.width * sensor->ir.data.height * 3,
      nullptr,
      nullptr);
    sensor->color.data.format = "B8G8R8A8_SRGB";
  }

  //Convert it into a depth POV representation
  k4a::image color_to_depth = sensor->param.transformation.color_image_to_depth_camera(sensor->depth.data.k4a_image, sensor->color.data.k4a_image);
  if(!color_to_depth.is_valid()) return;

  //Fill data structure
  sensor->color.cloud.name = "color_to_depth";
  sensor->color.cloud.k4a_image = color_to_depth;
  sensor->color.cloud.size = color_to_depth.get_size();
  sensor->color.cloud.width = color_to_depth.get_width_pixels();
  sensor->color.cloud.height = color_to_depth.get_height_pixels();
  sensor->color.cloud.buffer = color_to_depth.get_buffer();
  sensor->color.cloud.format = sensor->color.data.format;
  sensor->color.cloud.timestamp = sensor->color.data.timestamp;

  //---------------------------
  //color_to_depth.reset();
}

//Subfunction
string Data::retrieve_format_from_k4a(k4a_image_format_t color_format){
  string format = "";
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
void Data::retrieve_data_from_capture(k4a::image& image, vector<uint8_t>& data, string& format){
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
void Data::retrieve_bgra_from_mjpeg(k4a::image& image, vector<uint8_t>& data){
  //---------------------------

  int width = image.get_width_pixels();
  int height = image.get_height_pixels();
  int size = image.get_size();
  uint8_t* mpeg = image.get_buffer();
  vector<uint8_t> bgra(width * height * tjPixelSize[TJPF_RGBA]);
  int flags = TJFLAG_FASTDCT | TJFLAG_FASTUPSAMPLE;

  int ret = tjDecompress2(tj_handle, &mpeg[0], size, bgra.data(), width, 0, height, TJPF_RGBA, flags);
  if(ret != 0){
    cout<<"[error] MPEG convertion error"<<endl;
  }
  data = bgra;

  //Creat a new k4a image with RGBA data format
  image = k4a::image::create_from_buffer(K4A_IMAGE_FORMAT_COLOR_BGRA32, width, height, width * 4, data.data(), data.size(), nullptr, nullptr);

  //---------------------------
}
uint8_t* Data::retrieve_bgra_from_yuy2(const uint8_t* yuy2Image, int width, int height){
  uint8_t* bgrImage = new uint8_t[width * height * 3];
  //---------------------------

  for (int i = 0; i < width * height; i += 2) {
    uint8_t y0 = yuy2Image[2 * i];
    uint8_t u = yuy2Image[2 * i + 1];
    uint8_t y1 = yuy2Image[2 * i + 2];
    uint8_t v = yuy2Image[2 * i + 3];

    // Convert YUV to RGB
    int c = y0 - 16;
    int d = u - 128;
    int e = v - 128;

    int r0 = (298 * c + 409 * e + 128) >> 8;
    int g0 = (298 * c - 100 * d - 208 * e + 128) >> 8;
    int b0 = (298 * c + 516 * d + 128) >> 8;

    c = y1 - 16;

    int r1 = (298 * c + 409 * e + 128) >> 8;
    int g1 = (298 * c - 100 * d - 208 * e + 128) >> 8;
    int b1 = (298 * c + 516 * d + 128) >> 8;

    // Store BGR values
    bgrImage[3 * i] = static_cast<uint8_t>(std::max(0, std::min(255, b0)));
    bgrImage[3 * i + 1] = static_cast<uint8_t>(std::max(0, std::min(255, g0)));
    bgrImage[3 * i + 2] = static_cast<uint8_t>(std::max(0, std::min(255, r0)));
    bgrImage[3 * i + 3] = static_cast<uint8_t>(std::max(0, std::min(255, b1)));
    bgrImage[3 * i + 4] = static_cast<uint8_t>(std::max(0, std::min(255, g1)));
    bgrImage[3 * i + 5] = static_cast<uint8_t>(std::max(0, std::min(255, r1)));
  }

  //---------------------------
  return bgrImage;
}


}