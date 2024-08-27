#include "Infrared.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Core/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Infrared::Infrared(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dyn::prc::Node* node_processing = node_k4n->get_node_processing();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->dyn_struct = node_processing->get_dyn_struct();
  this->dat_image = node_element->get_dat_image();

  //---------------------------
}
Infrared::~Infrared(){}

//Main function
void Infrared::extract_data(std::shared_ptr<k4n::base::Sensor> sensor){
  //---------------------------

  this->retrieve_data(sensor);
  this->retrieve_image(sensor);

  //---------------------------
}

//Data function
void Infrared::retrieve_data(std::shared_ptr<k4n::base::Sensor> sensor){
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
  sensor->ir.data.format = retrieve_format(ir.get_format());
  sensor->ir.data.timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);
  type::uint8_to_vec_uint16(sensor->ir.data.buffer, sensor->ir.data.size, sensor->buffer_ir);

  //---------------------------
}
void Infrared::retrieve_image(std::shared_ptr<k4n::base::Sensor> sensor){
  //---------------------------

  //Image
  this->convert_image_into_color(sensor);
  sensor->ir.image.name = "Intensity";
  sensor->ir.image.size = sensor->ir.image.data.size();
  sensor->ir.image.width = sensor->ir.data.width;
  sensor->ir.image.height = sensor->ir.data.height;
  sensor->ir.image.format = "R8G8B8A8_SRGB";
  sensor->ir.image.timestamp = sensor->ir.data.timestamp;
  dat_image->add_image(sensor, std::make_shared<utl::media::Image>(sensor->ir.image));

  //---------------------------
}

//Subfunction
std::string Infrared::retrieve_format(k4a_image_format_t color_format){
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
void Infrared::convert_image_into_color(std::shared_ptr<k4n::base::Sensor> sensor){
  uint8_t* buffer = sensor->ir.data.buffer;
  uint16_t level_min = sensor->ir.config.level_min;
  uint16_t level_max = sensor->ir.config.level_max;
  //---------------------------

  std::vector<uint8_t> output = std::vector<uint8_t>(sensor->ir.data.size * 4, 0);

  for(int i=0, j=0; i<sensor->ir.data.size; i+=2, j+=4){
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

  sensor->ir.image.data = output;

  //---------------------------
}
void Infrared::find_ir_level(std::shared_ptr<k4n::base::Sensor> sensor){
  //---------------------------

  if(sensor->depth.config.mode == K4A_DEPTH_MODE_PASSIVE_IR){
    sensor->ir.config.level_min = 0;
    sensor->ir.config.level_max = 100;
  }
  else{
    sensor->depth.config.range_min = 0;
    sensor->depth.config.range_max = 1000;
  }

  //---------------------------
}

}
