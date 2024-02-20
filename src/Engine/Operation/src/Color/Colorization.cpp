#include "Colorization.h"

#include <Operation/Namespace.h>


namespace ope::color{

//Constructor / Destructor
Colorization::Colorization(){
  //---------------------------

  this->ope_heatmap = new eng::ope::Heatmap();

  //---------------------------
}
Colorization::~Colorization(){}

//Main function
void Colorization::make_colorization(utl::type::Data* data, int color_mode, int heatmap_mode){
  //---------------------------
/*
  switch(color_mode){
    case k4n::color::UNICOLOR:{
      this->colorization_unicolor(data);
      break;
    }
    case k4n::color::INTENSITY:{
      this->colorization_intensity(data);
      break;
    }
    case k4n::color::HEATMAP:{
      this->colorization_heatmap(data, heatmap_mode);
      break;
    }
    case k4n::color::STRUCTURE:{
      this->colorization_structure(data);
      break;
    }
  }
*/
  //---------------------------
}

//Subfunction
void Colorization::colorization_unicolor(utl::type::Data* data){
  //---------------------------

  data->rgb = vector<vec4>(data->rgb.size(), data->unicolor);

  //---------------------------
}
void Colorization::colorization_intensity(utl::type::Data* data){
  //---------------------------
/*
  for(int i=0; i<data->xyz.size(); i++){
    float Is = data->Is[i] / sensor->master->operation.intensity_division;
    data->rgb[i] = vec4(Is, Is, Is, 1);
  }
*/
  //---------------------------
}
void Colorization::colorization_heatmap(utl::type::Data* data, int heatmap_mode){
  //---------------------------
/*
  switch(sensor->master->operation.heatmap_mode){
    case k4n::color::heatmap::INTENSITY:{
      ope_heatmap->heatmap_intensity(vec_rgba, object, sensor->master->operation.intensity_division);
      break;
    }
    case k4n::color::heatmap::HEIGHT:{
      ope_heatmap->heatmap_height(vec_rgba, object, sensor->master->operation.range_height);
      break;
    }
    case k4n::color::heatmap::RANGE:{
      ope_heatmap->heatmap_range(vec_rgba, object);
      break;
    }
  }
*/
  //---------------------------
}
void Colorization::colorization_structure(utl::type::Data* data){
  //---------------------------

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
    data->rgb[i] = vec4(r, g, b, 1);
  }

  //---------------------------
}

}
