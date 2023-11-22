#include "K4A_infrared.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>


//Constructor / Destructor
K4A_infrared::K4A_infrared(){
  //---------------------------

  this->struct_kinect = new Struct_kinect();

  //---------------------------
}
K4A_infrared::~K4A_infrared(){}

//Main function
uint8_t* K4A_infrared::convert_ir_into_color(Struct_k4a_device* device){
  //---------------------------

  uint8_t* inputBuffer = device->data.ir.buffer;
  size_t size = device->data.depth.size;
  uint8_t* outputBuffer = new uint8_t[size*4];

  for(int i=0, j=0; i<size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<uint16_t*>(&inputBuffer[i]);

    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;

    if(r != 0){
      uint16_t range_min = device->depth.range_min;
      uint16_t range_max = device->depth.range_max;
      uint16_t clamped = r;
      clamped = std::min(clamped, range_max);
      clamped = std::max(clamped, range_min);
      float hue = (clamped - range_min) / static_cast<float>(range_max - range_min);
      constexpr float range = 2.f / 3.f;
      hue *= range;
      hue = range - hue;

      ImGui::ColorConvertHSVtoRGB(hue, 1.f, 1.f, R, G, B);
    }

    outputBuffer[j]     = static_cast<uint8_t>(R * 255);
    outputBuffer[j + 1] = static_cast<uint8_t>(G * 255);
    outputBuffer[j + 2] = static_cast<uint8_t>(B * 255);
    outputBuffer[j + 3] = 255;
  }

  //---------------------------
  return outputBuffer;
}
