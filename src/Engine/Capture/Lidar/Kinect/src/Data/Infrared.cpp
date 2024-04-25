#include "Infrared.h"

#include <Kinect/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Infrared::Infrared(){
  //---------------------------

  //---------------------------
}
Infrared::~Infrared(){}

//Main function
void Infrared::convert_ir_into_color(k4n::dev::Sensor* sensor, std::vector<uint8_t>& output){
  k4n::structure::Data* data = &sensor->ir.data;
  uint8_t* buffer = data->buffer;
  uint16_t level_min = sensor->ir.config.level_min;
  uint16_t level_max = sensor->ir.config.level_max;
  //---------------------------

  output.clear();
  output = std::vector<uint8_t>(data->size * 4, 0);

  for(int i=0, j=0; i<data->size; i+=2, j+=4){
    // Extract the 16-bit infrared value
    float ir = static_cast<uint16_t>(buffer[i]) | (static_cast<uint16_t>(buffer[i + 1]) << 8);

    // Apply intensity division
    ir /= sensor->master->operation.intensity_diviser;
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

  //---------------------------
}
void Infrared::find_ir_level(k4n::dev::Sensor* sensor){
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
