#include "Color.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Core/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Color::Color(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->dat_image = node_element->get_dat_image();

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->retrieve_data(sensor);
  this->retrieve_image(sensor);

  //Current timestamp
  sensor.timestamp.current = sensor.color.data.timestamp;

  //---------------------------
}

//Data function
void Color::retrieve_data(k4n::base::Sensor& sensor){
  //---------------------------

  //Get k4a image
  k4a::image color = sensor.device.capture->get_color_image();
  if(!color.is_valid()) return;

  //Data
  sensor.color.data.name = "color";
  sensor.color.data.k4a_image = color;
  sensor.color.data.size = color.get_size();
  sensor.color.data.width = color.get_width_pixels();
  sensor.color.data.height = color.get_height_pixels();
  sensor.color.data.buffer = color.get_buffer();
  sensor.color.data.format = retrieve_format(color.get_format());
  sensor.color.data.timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
}
void Color::retrieve_image(k4n::base::Sensor& sensor){
  //---------------------------

  //Image
  sensor.color.image.name = "Color";
  sensor.color.image.data = std::vector<uint8_t>(sensor.color.data.buffer, sensor.color.data.buffer + sensor.color.data.size);
  sensor.color.image.size = sensor.color.image.data.size();
  sensor.color.image.width = sensor.color.data.width;
  sensor.color.image.height = sensor.color.data.height;
  sensor.color.image.format = sensor.color.data.format;
  sensor.color.image.timestamp = sensor.color.data.timestamp;
  dat_image->add_image(sensor, std::make_shared<utl::media::Image>(sensor.color.image));

  //---------------------------
}

//Subfunction
std::string Color::retrieve_format(k4a_image_format_t color_format){
  std::string format = "";
  //---------------------------

  switch(color_format){
    case K4A_IMAGE_FORMAT_COLOR_MJPG:{
      format = "MJPEG";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_NV12:{
      format = "NV12";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_YUY2:{
      format = "YUY2";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_BGRA32:{
      format = "B8G8R8A8_SRGB";
      break;
    }
    default:{
      std::cout<<"[error] kinect color image format"<<std::endl;
      break;
    }
  }

  //---------------------------
  return format;
}
uint8_t* Color::retrieve_bgra_from_yuy2(const uint8_t* yuy2Image, int width, int height){
  uint8_t* bgrImage = new uint8_t[width * height * 3];
  //---------------------------

  /*if(sensor.color.data.format == "YUY2"){
    sensor.color.data.k4a_image = k4a::image::create_from_buffer(
      K4A_IMAGE_FORMAT_COLOR_BGRA32,
      sensor.ir.data.width,
      sensor.ir.data.height,
      sensor.ir.data.width * static_cast<int>(sizeof(uint32_t)),
      retrieve_bgra_from_yuy2(sensor.color.data.buffer, sensor.ir.data.width, sensor.ir.data.height),
      sensor.ir.data.width * sensor.ir.data.height * 3,
      nullptr,
      nullptr);
    sensor.color.data.format = "B8G8R8A8_SRGB";
  }*/

  for(int i = 0; i < width * height; i += 2){
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
void Color::retrieve_data_from_capture(k4a::image& image, std::vector<uint8_t>& data, std::string& format){
  //---------------------------
/*
this->tj_handle = tjInitDecompress();
tjDestroy(tj_handle);

  if(format == "MJPEG"){
    this->retrieve_bgra_from_mjpeg(image, data);
    format = "B8G8R8A8_SRGB";
  }else{
    uint8_t* image_data = image.get_buffer();
    size_t size = image.get_size();
    data = std::vector<uint8_t>(image_data, image_data + size);
    format = "B8G8R8A8_SRGB";
  }
*/
  //---------------------------
}
void Color::retrieve_bgra_from_mjpeg(k4a::image& image, std::vector<uint8_t>& data){
  //---------------------------
/*
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
*/
  //---------------------------
}

}
