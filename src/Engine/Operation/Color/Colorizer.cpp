#include "Colorizer.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>


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
      this->colorization_unicolor(entity, config);
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
void Colorizer::colorization_unicolor(utl::type::Entity* entity, ope::color::Configuration& config){
  utl::type::Data* data = entity->get_data();
  //---------------------------

  data->rgb = vector<vec4>(data->rgb.size(), config.unicolor);

  //---------------------------
}
void Colorizer::colorization_intensity(utl::type::Entity* entity, ope::color::Configuration& config){
  utl::type::Data* data = entity->get_data();
  //---------------------------

  for(int i=0; i<data->xyz.size(); i++){
    float Is = data->Is[i] / config.intensity_diviser;
    data->rgb[i] = vec4(Is, Is, Is, 1);
  }

  //---------------------------
}
void Colorizer::colorization_heatmap(utl::type::Entity* entity, ope::color::Configuration& config){
  //---------------------------

  switch(config.heatmap_mode){
    case ope::color::heatmap::INTENSITY:{
      ope_heatmap->heatmap_intensity(entity, config.intensity_diviser);
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

  // Calculate the number of points in each row and column
  int num_rows = data->height;
  int num_cols = data->width;

  // Define a color gradient from red to blue
  vector<vec3>& colormap = ope_colormap->get_colormap_selected();

  // Calculate the step size for color interpolation along rows and columns
  float row_step = 1.0f / (num_rows - 1);
  float col_step = 1.0f / (num_cols - 1);

  // Loop through the points and assign colors
  int index = 0;
  for(int i = 0; i < num_rows; ++i) {
      for(int j = 0; j < num_cols; ++j) {
          // Calculate the index in the colormap based on the normalized position
          int colormap_index = row_step * i * (colormap.size() - 1);

          // Interpolate between colors based on the index along rows
          const vec3& color1_row = colormap[colormap_index];
          const vec3& color2_row = colormap[colormap_index + 1];
          float t_row = static_cast<float>(i % num_rows) / (num_rows - 1); // Interpolation factor along rows
          vec3 interpolated_color_row = (1.0f - t_row) * color1_row + t_row * color2_row;

          // Interpolate between colors based on the index along columns
          const vec3& color1_col = colormap[colormap_index];
          const vec3& color2_col = colormap[colormap_index + 1];
          float t_col = static_cast<float>(j % num_cols) / (num_cols - 1); // Interpolation factor along columns
          vec3 interpolated_color_col = (1.0f - t_col) * color1_col + t_col * color2_col;

          // Combine the interpolated colors for rows and columns
          vec3 final_color = (interpolated_color_row + interpolated_color_col) * 0.5f;

          // Add the final color to the vector
          data->rgb[index] = vec4(final_color, 1.0f);
          ++index;
      }
  }

  //---------------------------
}

}
