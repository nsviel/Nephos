#include "Depth.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Depth::Depth(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();

  //---------------------------
}
Depth::~Depth(){}

//Main function
void Depth::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->retrieve_data(sensor);
  this->retrieve_raw_image(sensor);
  this->retrieve_colored_image(sensor);

  //---------------------------
}

//Data function
void Depth::retrieve_data(k4n::base::Sensor& sensor){
  //---------------------------

  //Get k4a image
  k4a::image depth = sensor.device.capture->get_depth_image();
  if(!depth.is_valid()) return;

  //Data
  sensor.depth.data.name = "depth";
  sensor.depth.data.k4a_image = depth;
  sensor.depth.data.width = depth.get_width_pixels();
  sensor.depth.data.height = depth.get_height_pixels();
  sensor.depth.data.buffer = depth.get_buffer();
  sensor.depth.data.size = depth.get_size();
  sensor.depth.data.format = retrieve_format(depth.get_format());
  sensor.depth.data.temperature = sensor.device.capture->get_temperature_c();
  sensor.depth.data.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  type::uint8_to_vec_uint16(sensor.depth.data.buffer, sensor.depth.data.size, sensor.info.buffer_depth);

  //---------------------------
}
void Depth::retrieve_raw_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Depth> image = sensor.depth.depth;
  //---------------------------

  //Image
  this->convert_buffer_into_uint16(sensor);
  image->size = image->data.size();
  image->width = sensor.depth.data.width;
  image->height = sensor.depth.data.height;
  image->format = "R16_UINT";
  //dat_image->add_image(sensor, image);

  //---------------------------
}
void Depth::retrieve_colored_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Image> image = sensor.depth.image;
  //---------------------------

  //Image
  this->convert_buffer_into_color(sensor);
  image->size = image->data.size();
  image->width = sensor.depth.data.width;
  image->height = sensor.depth.data.height;
  image->format = "RGBA8";
  image->timestamp = sensor.depth.data.timestamp;
  dat_image->add_image(sensor, image);

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
void Depth::convert_buffer_into_color(k4n::base::Sensor& sensor){
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

  sensor.depth.image->data = output;

  //---------------------------
}
void Depth::convert_buffer_into_uint16(k4n::base::Sensor& sensor){
  uint8_t* buffer = sensor.depth.data.buffer;
  //---------------------------

  std::vector<uint16_t> output = std::vector<uint16_t>(sensor.depth.data.size / 2, 0);

  // Iterate through the data array two bytes at a time
  for(size_t i=0, idx=0; i<sensor.depth.data.size; i+=2, idx++){
    // Combine two consecutive bytes into a uint16_t value
    uint16_t value = (static_cast<uint16_t>(buffer[i+1]) << 8) | static_cast<uint16_t>(buffer[i]);
    output[idx] = value;
  }

  sensor.depth.depth->data = output;

  //---------------------------
}
void Depth::find_depth_mode_range(k4n::base::Sensor& sensor){
  //---------------------------

  switch(sensor.depth.config.mode){
    case K4A_DEPTH_MODE_NFOV_2X2BINNED:{
      sensor.depth.config.range_min = 500;
      sensor.depth.config.range_max = 5800;
      break;
    }
    case K4A_DEPTH_MODE_NFOV_UNBINNED:{
      sensor.depth.config.range_min = 500;
      sensor.depth.config.range_max = 4000;
      break;
    }
    case K4A_DEPTH_MODE_WFOV_2X2BINNED:{
      sensor.depth.config.range_min = 250;
      sensor.depth.config.range_max = 3000;
      break;
    }
    case K4A_DEPTH_MODE_WFOV_UNBINNED:{
      sensor.depth.config.range_min = 250;
      sensor.depth.config.range_max = 2500;
      break;
    }
  }

  //---------------------------
}

}
