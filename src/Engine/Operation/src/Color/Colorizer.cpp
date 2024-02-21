#include "Colorizer.h"

#include <Operation/Namespace.h>


namespace ope::color{

//Constructor / Destructor
Colorizer::Colorizer(){
  //---------------------------

  this->ope_heatmap = new eng::ope::Heatmap();

  //---------------------------
}
Colorizer::~Colorizer(){}

//Main function
void Colorizer::make_colorization(utl::type::Entity* entity, ope::color::Configuration& config){
  //---------------------------

  switch(config.color_mode){
    case ope::color::UNICOLOR:{
      this->colorization_unicolor(entity);
      break;
    }
    case ope::color::INTENSITY:{
      this->colorization_intensity(entity, config);
      break;
    }
    case ope::color::HEATMAP:{
      this->colorization_heatmap(entity, config);
      break;
    }
    case ope::color::STRUCTURE:{
      this->colorization_structure(entity);
      break;
    }
  }

  //---------------------------
}

//Subfunction
void Colorizer::colorization_unicolor(utl::type::Entity* entity){
  utl::type::Data* data = entity->get_data();
  //---------------------------

  data->rgb = vector<vec4>(data->rgb.size(), data->unicolor);

  //---------------------------
}
void Colorizer::colorization_intensity(utl::type::Entity* entity, ope::color::Configuration& config){
  utl::type::Data* data = entity->get_data();
  //---------------------------

  for(int i=0; i<data->xyz.size(); i++){
    float Is = data->Is[i] / config.intensity_division;
    data->rgb[i] = vec4(Is, Is, Is, 1);
  }

  //---------------------------
}
void Colorizer::colorization_heatmap(utl::type::Entity* entity, ope::color::Configuration& config){
  //---------------------------

  switch(config.heatmap_mode){
    case ope::color::heatmap::INTENSITY:{
      ope_heatmap->heatmap_intensity(entity, config.intensity_division);
      break;
    }
    case ope::color::heatmap::HEIGHT:{
      ope_heatmap->heatmap_height(entity, config.heatmap_range_height);
      break;
    }
    case ope::color::heatmap::RANGE:{
      ope_heatmap->heatmap_range(entity);
      break;
    }
  }

  //---------------------------
}
void Colorizer::colorization_structure(utl::type::Entity* entity){
  utl::type::Data* data = entity->get_data();
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
