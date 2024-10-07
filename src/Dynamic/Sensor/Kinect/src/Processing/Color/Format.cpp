#include "Format.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::color{

//Constructor / Destructor
Format::Format(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();

  //---------------------------
}
Format::~Format(){}

//Main function
std::string Format::retrieve_format(k4a_image_format_t color_format){
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
      format = "RGBA8";
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

//Subfunction
uint8_t* Format::retrieve_bgra_from_yuy2(const uint8_t* yuy2Image, int width, int height){
  uint8_t* bgrImage = new uint8_t[width * height * 3];
  //---------------------------

  /*if(sensor.color.data.format == "YUY2"){
    sensor.color.data.image = k4a::image::create_from_buffer(
      K4A_IMAGE_FORMAT_COLOR_BGRA32,
      sensor.infra.data.width,
      sensor.infra.data.height,
      sensor.infra.data.width * static_cast<int>(sizeof(uint32_t)),
      retrieve_bgra_from_yuy2(sensor.color.data.buffer, sensor.infra.data.width, sensor.infra.data.height),
      sensor.infra.data.width * sensor.infra.data.height * 3,
      nullptr,
      nullptr);
    sensor.color.data.format = "BGRA8";
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
void Format::retrieve_data_from_capture(k4a::image& image, std::vector<uint8_t>& data, std::string& format){
  //---------------------------
/*
this->tj_handle = tjInitDecompress();
tjDestroy(tj_handle);

  if(format == "MJPEG"){
    this->retrieve_bgra_from_mjpeg(image, data);
    format = "BGRA8";
  }else{
    uint8_t* image_data = image.get_buffer();
    size_t size = image.get_size();
    data = std::vector<uint8_t>(image_data, image_data + size);
    format = "BGRA8";
  }
*/
  //---------------------------
}
void Format::retrieve_bgra_from_mjpeg(k4a::image& image, std::vector<uint8_t>& data){
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
void Format::convert_bgra_to_rgba(k4n::colornew::Structure& color){
/*  std::shared_ptr<utl::base::Image> image = color.image;
  //---------------------------

  // Retrieve the BGR(A) data from the sensor
  const uint8_t* bgr_buffer = sensor.color.data.buffer;
  size_t bgr_size = sensor.color.data.size;

  // Prepare a vector for RGBA data
  image->data.resize(bgr_size); // RGBA will have 4 bytes per pixel
  size_t rgba_index = 0;

  // Convert BGR to RGBA
  for (size_t i = 0; i < bgr_size; i += 4) {
    // Assuming the format is BGRA
    uint8_t b = bgr_buffer[i];     // B
    uint8_t g = bgr_buffer[i + 1]; // G
    uint8_t r = bgr_buffer[i + 2]; // R
    uint8_t a = bgr_buffer[i + 3]; // A

    // Fill the RGBA data
    image->data[rgba_index++] = r; // R
    image->data[rgba_index++] = g; // G
    image->data[rgba_index++] = b; // B
    image->data[rgba_index++] = a; // A
  }

  // Set the size of the RGBA image data
  image->size = rgba_index;
*/
  //---------------------------
}

}
