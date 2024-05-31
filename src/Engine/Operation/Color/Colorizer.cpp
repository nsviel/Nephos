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
void Colorizer::make_colorization(dat::base::Entity* entity, ope::color::Configuration& config){
  //---------------------------

  switch(config.color_mode){
    case ope::color::RGB:{
      this->colorization_rgb(entity, config);
      break;
    }
    case ope::color::UNICOLOR:{
      this->colorization_unicolor(entity, config);
      break;
    }
    case ope::color::INTENSITY:{
      this->colorization_intensity(entity, config);
      break;
    }
    case ope::color::NORMAL:{
      this->colorization_normal(entity, config);
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
void Colorizer::colorization_rgb(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  if(data->rgba.size() == 0) data->rgba = std::vector<glm::vec4>(data->xyz.size(), glm::vec4(0.0f));
  for(int i=0; i<data->rgb.size(); i++){
    glm::vec3& rgb = data->rgb[i];
    data->rgba[i] = glm::vec4(rgb.x, rgb.y, rgb.z, 1);
  }

  //---------------------------
}
void Colorizer::colorization_unicolor(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  if(data->rgba.size() == 0) data->rgba = std::vector<glm::vec4>(data->xyz.size(), glm::vec4(0.0f));
  data->rgba = std::vector<glm::vec4>(data->rgba.size(), config.unicolor);

  //---------------------------
}
void Colorizer::colorization_intensity(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  if(data->rgba.size() == 0) data->rgba = std::vector<glm::vec4>(data->xyz.size(), glm::vec4(0.0f));
  for(int i=0; i<data->Is.size(); i++){
    float Is = data->Is[i] / config.intensity_diviser;
    data->rgba[i] = glm::vec4(Is, Is, Is, 1);
  }

  //---------------------------
}
void Colorizer::colorization_normal(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  if(data->rgba.size() == 0) data->rgba = std::vector<glm::vec4>(data->xyz.size(), glm::vec4(0.0f));
  std::vector<glm::vec3>& Nxyz = data->Nxyz;

  //Compute heatmap
  #pragma omp parallel for
  for(int i=0; i<Nxyz.size(); i++){
    float R = (1 + Nxyz[i].x) / 2;
    float G = (1 + Nxyz[i].y) / 2;
    float B = (1 + Nxyz[i].z) / 2;

    data->rgba[i] = glm::vec4(R, G, B, 1.0f);
  }

  //---------------------------
}
void Colorizer::colorization_heatmap(dat::base::Entity* entity, ope::color::Configuration& config){
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
void Colorizer::colorization_structure(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  // Calculate the number of points in each row and column
  int num_rows = data->height;
  int num_cols = data->width;

  // Define a color gradient from red to blue
  std::vector<glm::vec3>& colormap = ope_colormap->get_colormap_selected();

  // Calculate the step size for color interpolation along rows and columns
  float row_step = 1.0f / (num_rows - 1);
  float col_step = 1.0f / (num_cols - 1);

  // Loop through the points and assign colors
  int index = 0;
  for(int i = 0; i < num_rows; ++i){
    for(int j = 0; j < num_cols; ++j){
      // Calculate the index in the colormap based on the normalized position
      int colormap_index = row_step * i * (colormap.size() - 1);

      // Interpolate between colors based on the index along rows
      const glm::vec3& color1_row = colormap[colormap_index];
      const glm::vec3& color2_row = colormap[colormap_index + 1];
      float t_row = static_cast<float>(i % num_rows) / (num_rows - 1); // Interpolation factor along rows
      glm::vec3 interpolated_color_row = (1.0f - t_row) * color1_row + t_row * color2_row;

      // Interpolate between colors based on the index along columns
      const glm::vec3& color1_col = colormap[colormap_index];
      const glm::vec3& color2_col = colormap[colormap_index + 1];
      float t_col = static_cast<float>(j % num_cols) / (num_cols - 1); // Interpolation factor along columns
      glm::vec3 interpolated_color_col = (1.0f - t_col) * color1_col + t_col * color2_col;

      // Combine the interpolated colors for rows and columns
      glm::vec3 final_color = (interpolated_color_row + interpolated_color_col) * 0.5f;

      // Add the final color to the vector
      data->rgba[index] = glm::vec4(final_color, 1.0f);
      ++index;
    }
  }

  //---------------------------
}

}
