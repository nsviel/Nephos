#include "Format.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::depth{

//Constructor / Destructor
Format::Format(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->dat_depth = node_image->get_dat_depth();

  //---------------------------
}
Format::~Format(){}

//Main function
std::string Format::retrieve_format(k4a_image_format_t color_format){
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

//Subfunction
void Format::convert_buffer_into_color(k4n::base::Sensor& sensor){
  uint8_t* buffer = sensor.depth.data.buffer;
  uint16_t range_min = sensor.depth.config.range_min;
  uint16_t range_max = sensor.depth.config.range_max;
  //---------------------------

  std::vector<uint8_t> output = std::vector<uint8_t>(sensor.depth.data.size * 4, 0);

  for(int i=0, j=0; i<sensor.depth.data.size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<const uint16_t*>(&buffer[i]);

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

    output[j] = static_cast<uint8_t>(R * 255);
    output[j + 1] = static_cast<uint8_t>(G * 255);
    output[j + 2] = static_cast<uint8_t>(B * 255);
    output[j + 3] = 255;
  }

  sensor.depth.texture.image->data = output;

  //---------------------------
}
void Format::convert_buffer_into_uint16(k4n::base::Sensor& sensor){
  uint8_t* buffer = sensor.depth.data.buffer;
  //---------------------------

  std::vector<uint16_t> output = std::vector<uint16_t>(sensor.depth.data.size / 2, 0);

  // Iterate through the data array two bytes at a time
  for(size_t i=0, idx=0; i<sensor.depth.data.size; i+=2, idx++){
    // Combine two consecutive bytes into a uint16_t value
    uint16_t value = (static_cast<uint16_t>(buffer[i+1]) << 8) | static_cast<uint16_t>(buffer[i]);
    output[idx] = value;
  }

  sensor.depth.texture.depth->data = output;

  //---------------------------
}

}
