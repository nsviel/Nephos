#include "Depth.h"

#include <K4N/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Depth::Depth(){
  //---------------------------

  //---------------------------
}
Depth::~Depth(){}

//Main function
void Depth::convert_depth_into_color(k4n::dev::Sensor* sensor, std::vector<uint8_t>& output){
  k4n::structure::Data* data = &sensor->depth.data;
  uint8_t* inputBuffer = data->buffer;
  uint16_t range_min = sensor->depth.config.range_min;
  uint16_t range_max = sensor->depth.config.range_max;
  //---------------------------

  output.clear();
  output = std::vector<uint8_t>(data->size * 4, 0);

  for(int i=0, j=0; i<data->size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<const uint16_t*>(&inputBuffer[i]);

    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;

    if (r != 0) {
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

  //---------------------------
}
void Depth::convert_depth_into_color_(k4n::dev::Sensor* sensor){
  k4n::structure::Data* data = &sensor->depth.data;
  uint8_t* inputBuffer = data->buffer;
  uint16_t range_min = sensor->depth.config.range_min;
  uint16_t range_max = sensor->depth.config.range_max;
  //---------------------------

  uint8_t* outputBuffer = new uint8_t[data->size * 4]();
  int cpt = 0;
  for(int i=0, j=0; i<data->size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<const uint16_t*>(&inputBuffer[i]);

    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;

    if (r != 0) {
      uint16_t clamped = r;
      clamped = std::min(clamped, range_max);
      clamped = std::max(clamped, range_min);
      float hue = (clamped - range_min) / static_cast<float>(range_max - range_min);
      constexpr float range = 2.f / 3.f;
      hue *= range;
      hue = range - hue;

      ImGui::ColorConvertHSVtoRGB(hue, 1.f, 1.f, R, G, B);
    }

    outputBuffer[j] = static_cast<uint8_t>(R * 255);
    outputBuffer[j + 1] = static_cast<uint8_t>(G * 255);
    outputBuffer[j + 2] = static_cast<uint8_t>(B * 255);
    outputBuffer[j + 3] = 255;
    cpt = cpt +4;
  }

  data->size = cpt;
  data->buffer = outputBuffer;

  //---------------------------
}
void Depth::find_depth_mode_range(k4n::dev::Sensor* sensor){
  //---------------------------

  if(sensor->depth.config.mode == K4A_DEPTH_MODE_NFOV_2X2BINNED){
    sensor->depth.config.range_min = 500;
    sensor->depth.config.range_max = 5800;
  }
  else if(sensor->depth.config.mode == K4A_DEPTH_MODE_NFOV_UNBINNED){
    sensor->depth.config.range_min = 500;
    sensor->depth.config.range_max = 4000;
  }
  else if(sensor->depth.config.mode == K4A_DEPTH_MODE_WFOV_2X2BINNED){
    sensor->depth.config.range_min = 250;
    sensor->depth.config.range_max = 3000;
  }
  else if(sensor->depth.config.mode == K4A_DEPTH_MODE_WFOV_UNBINNED){
    sensor->depth.config.range_min = 250;
    sensor->depth.config.range_max = 2500;
  }

  //---------------------------
}

}
