#include "Colorizer.h"

#include <Operation/Namespace.h>


namespace ope::color{

//Constructor / Destructor
Colorizer::Colorizer(){
  //---------------------------

  this->ope_heatmap = new ope::color::Heatmap();
  this->ope_colormap = new ope::color::Colormap();

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
  vector<vec3>& colormap = ope_colormap->get_colormap_selected();

  // Calculate the step size for color interpolation
  float step = 1.0f / (data->xyz.size() - 1);

  // Loop through the points and assign colors
  vector<vec4> rgb;
  for(int i = 0; i < data->xyz.size(); ++i) {
    // Calculate the index in the colormap based on the normalized position
    int colormap_index = step * float(i) * colormap.size() - 1;

    // Interpolate between colors based on the index
    float t = step * i * (colormap.size() - 1) - colormap_index;
    const vec3& color1 = colormap[colormap_index];
    const vec3& color2 = colormap[colormap_index + 1];
    vec3 interpolated_color = (1.0f - t) * color1 + t * color2;

    // Add the interpolated color to the vector
    data->rgb[i] = vec4(interpolated_color, 1.0f);
  }

  //---------------------------
}

}
