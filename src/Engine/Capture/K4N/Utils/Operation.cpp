#include "Operation.h"


namespace k4n::utils{

//Constructor / Destructor
Operation::Operation(){
  //---------------------------

  this->ope_heatmap = new eng::ope::Heatmap();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::make_colorization(k4n::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba){
  //---------------------------

  switch(k4n_sensor->cloud.color_mode){
    case 1:{//Colored unicolor
      vec_rgba = vector<vec4> (k4n_sensor->cloud.nb_point, k4n_sensor->object->data->unicolor);
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
void Operation::colorization_intensity(k4n::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba){
  //---------------------------

  vec_rgba.clear();
  vec_rgba.reserve(k4n_sensor->cloud.nb_point);
  for(int i=0; i<k4n_sensor->cloud.nb_point; i++){
    float Is = k4n_sensor->object->data->Is[i] / k4n_sensor->cloud.intensity_division;
    vec_rgba.push_back(vec4(Is, Is, Is, 1));
  }

  //---------------------------
}
void Operation::colorization_heatmap(k4n::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba){
  //---------------------------

  switch(k4n_sensor->cloud.heatmap_mode){
    case 0:{//Intensity
      vec_rgba = ope_heatmap->heatmap_intensity(k4n_sensor->object, k4n_sensor->cloud.intensity_division);
      break;
    }
    case 1:{//Height
      vec_rgba = ope_heatmap->heatmap_height(k4n_sensor->object, k4n_sensor->cloud.range_height);
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
