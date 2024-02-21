#include "Operation.h"

#include <K4N/Namespace.h>
#include <Operation/Namespace.h>


namespace k4n::utils{

//Constructor / Destructor
Operation::Operation(){
  //---------------------------

  this->ope_heatmap = new eng::ope::Heatmap();

  //---------------------------
}
Operation::~Operation(){}

//Main function
float Operation::find_mkv_ts_beg(string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_BEGIN);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_next_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_beg = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_beg;
}
float Operation::find_mkv_ts_end(string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_END);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_previous_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_end = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_end;
}

//Colorization function
void Operation::make_colorization(k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba){
  //---------------------------

  ope::color::Configuration config;
  config.color_mode = sensor->master->operation.color_mode;
  config.heatmap_mode = sensor->master->operation.heatmap_mode;
  config.intensity_division = sensor->master->operation.intensity_division;
  config.heatmap_range_height = sensor->master->operation.range_height;
/*
  switch(sensor->master->operation.color_mode){
    case k4n::color::UNICOLOR:{
      utl::type::Data* data = sensor->get_data();
      vec_rgba = vector<vec4>(vec_rgba.size(), data->unicolor);
      break;
    }
    case k4n::color::INTENSITY:{
      this->colorization_intensity(sensor, vec_rgba);
      break;
    }
    case k4n::color::HEATMAP:{
      this->colorization_heatmap(sensor, vec_rgba);
      break;
    }
    case k4n::color::STRUCTURE:{
      this->colorization_structure(sensor, vec_rgba);
      break;
    }
  }
*/
  //---------------------------
}
void Operation::colorization_intensity(k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba){
  utl::type::Data* data = sensor->get_data();
  //---------------------------

  for(int i=0; i<data->xyz.size(); i++){
    float Is = data->Is[i] / sensor->master->operation.intensity_division;
    vec_rgba[i] = vec4(Is, Is, Is, 1);
  }

  //---------------------------
}
void Operation::colorization_heatmap(k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba){
  utl::entity::Object* object = sensor->get_object();
  //---------------------------

/*

  switch(sensor->master->operation.heatmap_mode){
    case k4n::color::heatmap::INTENSITY:{
      ope_heatmap->heatmap_intensity(object, sensor->master->operation.intensity_division);
      break;
    }
    case k4n::color::heatmap::HEIGHT:{
      ope_heatmap->heatmap_height(object, sensor->master->operation.range_height);
      break;
    }
    case k4n::color::heatmap::RANGE:{
      ope_heatmap->heatmap_range(object);
      break;
    }
  }
*/
  //---------------------------
}
void Operation::colorization_structure(k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba){
  //---------------------------

  utl::type::Data* data = sensor->get_data();

  // Define a color gradient from red to blue
  const vec3 green(0.0f, 1.0f, 0.0f);
  const vec3 blue(0.0f, 0.0f, 1.0f);

  // Calculate the step size for color interpolation
  float step = 1.0f / (data->xyz.size() - 1);

  // Loop through the points and assign colors
  vector<vec4> rgb;
  for (size_t i = 0; i < data->xyz.size(); ++i) {
    // Interpolate between red and blue based on the index
    float t = step * i;
    float r = (1.0f - t) * green.r + t * blue.r;
    float g = (1.0f - t) * green.g + t * blue.g;
    float b = (1.0f - t) * green.b + t * blue.b;

    // Add the interpolated color to the vector
    vec_rgba[i] = vec4(r, g, b, 1);
  }

  //---------------------------
}

}
