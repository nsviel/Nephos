#include "Format.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>
#include <Processing/Namespace.h>


namespace k4n::infrared{

//Constructor / Destructor
Format::Format(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();
  dyn::prc::Node* node_processing = node_k4n->get_node_processing();

  this->dat_image = node_image->get_dat_image();
  this->dat_depth = node_image->get_dat_depth();
  this->dyn_struct = node_processing->get_dyn_struct();

  //---------------------------
}
Format::~Format(){}

//Main function
std::string Format::retrieve_format(k4a_image_format_t color_format){
  std::string format = "";
  //---------------------------

  switch(color_format){
    case K4A_IMAGE_FORMAT_IR16:{
      format = "IR16";
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
      std::cout<<"[error] kinect infrared image format"<<std::endl;
      break;
    }
  }

  //---------------------------
  return format;
}

//Subfunction
void Format::convert_buffer_into_color(k4n::base::Sensor& sensor){
  uint8_t* buffer = sensor.infra.data.buffer;
  uint16_t level_min = sensor.infra.config.level_min;
  uint16_t level_max = sensor.infra.config.level_max;
  //---------------------------

  std::vector<uint8_t> output = std::vector<uint8_t>(sensor.infra.data.size * 4, 0);

  for(int i=0, j=0; i<sensor.infra.data.size; i+=2, j+=4){
    // Extract the 16-bit infrared value
    float ir = static_cast<uint16_t>(buffer[i]) | (static_cast<uint16_t>(buffer[i + 1]) << 8);

    // Apply intensity division
    ir /= dyn_struct->operation.intensity.diviser;
    if(ir < 0) ir = 0;
    if(ir > 1) ir = 1;

    // Convert the float value to uint8_t
    uint8_t value = static_cast<uint8_t>(ir * 255.0f);

    // Assign the value to the output vector for each channel (R, G, B, Alpha)
    output[j] = value;
    output[j + 1] = value;
    output[j + 2] = value;
    output[j + 3] = 255;
  }

  sensor.infra.texture.image->data = output;

  //---------------------------
}
void Format::convert_buffer_into_uint16(k4n::base::Sensor& sensor){
  uint8_t* buffer = sensor.infra.data.buffer;
  //---------------------------

  std::vector<uint16_t> output = std::vector<uint16_t>(sensor.infra.data.size / 2, 0);

  // Iterate through the data array two bytes at a time
  for(size_t i=0, idx=0; i<sensor.infra.data.size; i+=2, idx++){
    // Combine two consecutive bytes into a uint16_t value
    uint16_t value = (static_cast<uint16_t>(buffer[i+1]) << 8) | static_cast<uint16_t>(buffer[i]);
    output[idx] = value;
  }

  sensor.infra.texture.depth->data = output;

  //---------------------------
}
void Format::find_ir_level(k4n::base::Sensor& sensor){
  //---------------------------

  if(sensor.depth.config.mode == K4A_DEPTH_MODE_PASSIVE_IR){
    sensor.infra.config.level_min = 0;
    sensor.infra.config.level_max = 100;
  }
  else{
    sensor.depth.config.range_min = 0;
    sensor.depth.config.range_max = 1000;
  }

  //---------------------------
}

}
