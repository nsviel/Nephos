#include "Depth.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Depth::Depth(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->dat_image = node_data->get_dat_image();

  //---------------------------
}
Depth::~Depth(){}

//Main function
void Depth::extract_data(k4n::base::Sensor* sensor){
  //---------------------------

  this->retrieve_data(sensor);
  this->retrieve_image(sensor);

  //---------------------------
}

//Data function
void Depth::retrieve_data(k4n::base::Sensor* sensor){
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
  sensor->depth.data.format = retrieve_format(depth.get_format());
  sensor->depth.data.temperature = sensor->device.capture->get_temperature_c();
  sensor->depth.data.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  utl::casting::uint8_to_vec_uint16(sensor->depth.data.buffer, sensor->depth.data.size, sensor->buffer_depth);

  //---------------------------
}
void Depth::retrieve_image(k4n::base::Sensor* sensor){
  //---------------------------

  //Colorization
  std::vector<uint8_t> buffer;
  this->convert_image_into_color(sensor, buffer);

  //Image
  sensor->depth.image.name = "Depth";
  sensor->depth.image.data = buffer;
  sensor->depth.image.size = buffer.size();
  sensor->depth.image.width = sensor->depth.data.width;
  sensor->depth.image.height = sensor->depth.data.height;
  sensor->depth.image.format = "R8G8B8A8_SRGB";
  sensor->depth.image.type = utl::media::DEPTH;
  sensor->depth.image.timestamp = sensor->depth.data.timestamp;
  dat_image->add_image(sensor, &sensor->depth.image);

  //---------------------------
}

//Subfunction
std::string Depth::retrieve_format(k4a_image_format_t color_format){
  std::string format = "";
  //---------------------------

  switch(color_format){
    case K4A_IMAGE_FORMAT_DEPTH16:{
      format = "DEPTH16";
      break;
    }
    case K4A_IMAGE_FORMAT_CUSTOM8:{
      format = "CUSTOM8";
      break;
    }
    case K4A_IMAGE_FORMAT_CUSTOM16:{
      format = "CUSTOM16";
      break;
    }
    default:{
      std::cout<<"[error] kinect depth image format"<<std::endl;
      break;
    }
  }

  //---------------------------
  return format;
}
void Depth::convert_image_into_color(k4n::base::Sensor* sensor, std::vector<uint8_t>& buffer){
  uint8_t* inputBuffer = sensor->depth.data.buffer;
  uint16_t range_min = sensor->depth.config.range_min;
  uint16_t range_max = sensor->depth.config.range_max;
  //---------------------------

  buffer = std::vector<uint8_t>(sensor->depth.data.size * 4, 0);

  for(int i=0, j=0; i<sensor->depth.data.size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<const uint16_t*>(&inputBuffer[i]);

    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;

    if(r != 0){
      uint16_t clamped = r;
      clamped = std::min(clamped, range_max);
      clamped = std::max(clamped, range_min);
      float hue = (clamped - range_min) / static_cast<float>(range_max - range_min);
      constexpr float range = 2.f / 3.f;
      hue *= range;
      hue = range - hue;

      ImGui::ColorConvertHSVtoRGB(hue, 1.f, 1.f, R, G, B);
    }

    buffer[j] = static_cast<uint8_t>(R * 255);
    buffer[j + 1] = static_cast<uint8_t>(G * 255);
    buffer[j + 2] = static_cast<uint8_t>(B * 255);
    buffer[j + 3] = 255;
  }

  //---------------------------
}
void Depth::find_depth_mode_range(k4n::base::Sensor* sensor){
  //---------------------------

  switch(sensor->depth.config.mode){
    case K4A_DEPTH_MODE_NFOV_2X2BINNED:{
      sensor->depth.config.range_min = 500;
      sensor->depth.config.range_max = 5800;
      break;
    }
    case K4A_DEPTH_MODE_NFOV_UNBINNED:{
      sensor->depth.config.range_min = 500;
      sensor->depth.config.range_max = 4000;
      break;
    }
    case K4A_DEPTH_MODE_WFOV_2X2BINNED:{
      sensor->depth.config.range_min = 250;
      sensor->depth.config.range_max = 3000;
      break;
    }
    case K4A_DEPTH_MODE_WFOV_UNBINNED:{
      sensor->depth.config.range_min = 250;
      sensor->depth.config.range_max = 2500;
      break;
    }
  }

  //---------------------------
}

}
