#include "Infrared.h"


namespace eng::kinect::data{

//Constructor / Destructor
Infrared::Infrared(){
  //---------------------------


  //---------------------------
}
Infrared::~Infrared(){}

//Main function
std::vector<uint8_t> Infrared::convert_ir_into_color(K4A_device* device){
  std::vector<uint8_t>& inputBuffer = device->ir.image.data;
  uint16_t level_min = device->ir.config.level_min;
  uint16_t level_max = device->ir.config.level_max;
  //---------------------------

  std::vector<uint8_t> outputBuffer(inputBuffer.size() * 4, 0);

  for (int i = 0, j = 0; i < inputBuffer.size(); i += 2, j += 4) {
      uint16_t r = *reinterpret_cast<const uint16_t*>(&inputBuffer[i]);

      r = std::min(r, level_max);
      uint8_t value = static_cast<uint8_t>((r - level_min) * (255.0f / (level_max - level_min)));

      outputBuffer[j] = value;
      outputBuffer[j + 1] = value;
      outputBuffer[j + 2] = value;
      outputBuffer[j + 3] = 255;
  }

  //---------------------------
  return outputBuffer;
}
void Infrared::find_ir_level(K4A_device* device){
  //---------------------------

  if(device->depth.config.mode == K4A_DEPTH_MODE_PASSIVE_IR){
    device->ir.config.level_min = 0;
    device->ir.config.level_max = 100;
  }
  else{
    device->depth.config.range_min = 0;
    device->depth.config.range_max = 1000;
  }

  //---------------------------
}

}
