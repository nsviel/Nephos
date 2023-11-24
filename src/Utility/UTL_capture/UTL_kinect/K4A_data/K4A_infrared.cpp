#include "K4A_infrared.h"

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_swarm.h>


//Constructor / Destructor
K4A_infrared::K4A_infrared(Struct_swarm* struct_swarm){
  //---------------------------

  this->struct_swarm = struct_swarm;

  //---------------------------
}
K4A_infrared::~K4A_infrared(){}

//Main function
uint8_t* K4A_infrared::convert_ir_into_color(K4A_device* device){
  //---------------------------

  uint8_t* inputBuffer = device->data.ir.buffer;
  size_t size = device->data.ir.size;
  uint8_t* outputBuffer = new uint8_t[size*4];
  uint16_t level_min = device->ir.level_min;
  uint16_t level_max = device->ir.level_max;

  for(int i=0, j=0; i<size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<uint16_t*>(&inputBuffer[i]);

    r = std::min(r, level_max);
    uint8_t value = static_cast<uint8_t>((r - level_min) * (255.0f / (level_max - level_min)));

    outputBuffer[j]     = value;
    outputBuffer[j + 1] = value;
    outputBuffer[j + 2] = value;
    outputBuffer[j + 3] = 255;
  }

  //---------------------------
  return outputBuffer;
}
void K4A_infrared::find_ir_level(K4A_device* device){
  //---------------------------

  if(device->depth.mode == K4A_DEPTH_MODE_PASSIVE_IR){
    device->ir.level_min = 0;
    device->ir.level_max = 100;
  }
  else{
    device->depth.range_min = 0;
    device->depth.range_max = 1000;
  }

  //---------------------------
}
