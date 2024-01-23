#include "Operation.h"


namespace eng::k4n::utils{

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
void Operation::make_colorization(eng::k4n::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba){
  //---------------------------

  switch(k4n_sensor->master->operation.color_mode){
    case 1:{//Colored unicolor
      vec_rgba = vector<vec4> (k4n_sensor->object->data->nb_point, k4n_sensor->object->data->unicolor);
      break;
    }
    case 2:{//White unicolor
      this->colorization_intensity(k4n_sensor, vec_rgba);
      break;
    }
    case 3:{//Heatmap
      this->colorization_heatmap(k4n_sensor, vec_rgba);
      break;
    }
  }

  //---------------------------
}
void Operation::colorization_intensity(eng::k4n::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba){
  //---------------------------

  vec_rgba.clear();
  vec_rgba.reserve(k4n_sensor->object->data->nb_point);
  for(int i=0; i<k4n_sensor->object->data->nb_point; i++){
    float Is = k4n_sensor->object->data->Is[i] / k4n_sensor->master->operation.intensity_division;
    vec_rgba.push_back(vec4(Is, Is, Is, 1));
  }

  //---------------------------
}
void Operation::colorization_heatmap(eng::k4n::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba){
  //---------------------------

  switch(k4n_sensor->master->operation.heatmap_mode){
    case 0:{//Intensity
      vec_rgba = ope_heatmap->heatmap_intensity(k4n_sensor->object, k4n_sensor->master->operation.intensity_division);
      break;
    }
    case 1:{//Height
      vec_rgba = ope_heatmap->heatmap_height(k4n_sensor->object, k4n_sensor->master->operation.range_height);
      break;
    }
    case 2:{//Range
      vec_rgba = ope_heatmap->heatmap_range(k4n_sensor->object);
      break;
    }
  }

  //---------------------------
}

}
