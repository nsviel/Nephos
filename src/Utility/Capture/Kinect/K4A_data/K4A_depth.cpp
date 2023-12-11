#include "K4A_depth.h"


//Constructor / Destructor
K4A_depth::K4A_depth(){
  //---------------------------

  //---------------------------
}
K4A_depth::~K4A_depth(){}

//Main function
uint8_t* K4A_depth::convert_depth_into_color(K4A_device* device){
  //---------------------------

  uint8_t* inputBuffer = device->data.depth.buffer;
  size_t size = device->data.depth.size;
  uint8_t* outputBuffer = new uint8_t[size*4];
  uint16_t range_min = device->depth.range_min;
  uint16_t range_max = device->depth.range_max;

  for(int i=0, j=0; i<size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<uint16_t*>(&inputBuffer[i]);

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

    outputBuffer[j]     = static_cast<uint8_t>(R * 255);
    outputBuffer[j + 1] = static_cast<uint8_t>(G * 255);
    outputBuffer[j + 2] = static_cast<uint8_t>(B * 255);
    outputBuffer[j + 3] = 255;
  }

  //---------------------------
  return outputBuffer;
}
void K4A_depth::find_depth_mode_range(K4A_device* device){
  //---------------------------

  if(device->depth.mode == K4A_DEPTH_MODE_NFOV_2X2BINNED){
    device->depth.range_min = 500;
    device->depth.range_max = 5800;
  }
  else if(device->depth.mode == K4A_DEPTH_MODE_NFOV_UNBINNED){
    device->depth.range_min = 500;
    device->depth.range_max = 4000;
  }
  else if(device->depth.mode == K4A_DEPTH_MODE_WFOV_2X2BINNED){
    device->depth.range_min = 250;
    device->depth.range_max = 3000;
  }
  else if(device->depth.mode == K4A_DEPTH_MODE_WFOV_UNBINNED){
    device->depth.range_min = 250;
    device->depth.range_max = 2500;
  }

  //---------------------------
}
