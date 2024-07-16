#include "Colorizer.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>


namespace ope::color{

//Constructor / Destructor
Colorizer::Colorizer(){
  //---------------------------

  this->ope_heatmap = new ope::color::Heatmap();
  this->utl_attribut = new utl::base::Attribut();

  //---------------------------
}
Colorizer::~Colorizer(){}

//Main function
void Colorizer::make_colorization(dat::base::Entity* entity, ope::color::Configuration& config){
  //---------------------------

  if(entity->data.rgba.size() != entity->data.xyz.size()){
    entity->data.rgba = std::vector<glm::vec4>(entity->data.xyz.size(), glm::vec4(0.0f));
  }

  switch(config.color_mode){
    case ope::color::RGB:{
      this->colorization_rgb(entity, config);
      break;
    }
    case ope::color::UNICOLOR:{
      this->colorization_unicolor(entity, config);
      break;
    }
    case ope::color::LOCATION:{
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

  for(int i=0; i<data->rgb.size(); i++){
    glm::vec3& rgb = data->rgb[i];
    data->rgba[i] = glm::vec4(rgb.x, rgb.y, rgb.z, 1);
  }

  //---------------------------
}
void Colorizer::colorization_unicolor(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  data->rgba = std::vector<glm::vec4>(data->rgba.size(), config.unicolor);

  //---------------------------
}
void Colorizer::colorization_intensity(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  std::vector<float>& vec_I = utl_attribut->get_attribut_data(data, "I");
  for(int i=0; i<vec_I.size(); i++){
    float& Is = vec_I[i];
    data->rgba[i] = glm::vec4(Is, Is, Is, 1);
  }

  //---------------------------
}
void Colorizer::colorization_intensity_inv(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  std::vector<float>& vec_I = utl_attribut->get_attribut_data(data, "I");
  for(int i=0; i<vec_I.size(); i++){
    float Iinv = 1 - vec_I[i];
    data->rgba[i] = glm::vec4(Iinv, Iinv, Iinv, 1);
  }

  //---------------------------
}
void Colorizer::colorization_intensity_cor(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  std::vector<float>& vec_Icor = utl_attribut->get_attribut_data(data, "I_cor");
  for(int i=0; i<vec_Icor.size(); i++){
    float& Is = vec_Icor[i];
    data->rgba[i] = glm::vec4(Is, Is, Is, 1);
  }

  //---------------------------
}
void Colorizer::colorization_incidence_angle(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  std::vector<float>& vec_It = utl_attribut->get_attribut_data(data, "It");
  for(int i=0; i<vec_It.size(); i++){
    float It = vec_It[i];

    if(std::isnan(It)){
      It = 1;
    }else{
      It = It / 90;
    }

    data->rgba[i] = glm::vec4(It, It, It, 1);
  }

  //---------------------------
}
void Colorizer::colorization_intensity_cal(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  //---------------------------

  std::vector<float>& vec_Ical = utl_attribut->get_attribut_data(data, "I_cal");
  for(int i=0; i<vec_Ical.size(); i++){
    float& Is = vec_Ical[i];
    data->rgba[i] = glm::vec4(Is, Is, Is, 1);
  }

  //---------------------------
}
void Colorizer::colorization_normal(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;
  //---------------------------

  std::vector<glm::vec3>& Nxyz = data->Nxyz;

  //Compute heatmap
  #pragma omp parallel for
  for(int i=0; i<Nxyz.size(); i++){
    glm::vec4 normal = glm::vec4(Nxyz[i], 1.0) * pose->rotat;

    float R = (1 + normal.x) / 2;
    float G = (1 + normal.y) / 2;
    float B = (1 + normal.z) / 2;

    data->rgba[i] = glm::vec4(R, G, B, 1.0f);
  }

  //---------------------------
}
void Colorizer::colorization_location(dat::base::Entity* entity, ope::color::Configuration& config){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;

  //Compute heatmap
  #pragma omp parallel for
  for(int i=0; i<xyz.size(); i++){
    glm::vec4 normal = glm::vec4(xyz[i], 1.0) * pose->model;

    float R = (1 + normal.x) / 2;
    float G = (1 + normal.y) / 2;
    float B = (1 + normal.z) / 2;

    data->rgba[i] = glm::vec4(R, G, B, 1.0f);
  }

  //---------------------------
}
void Colorizer::colorization_heatmap(dat::base::Entity* entity, ope::color::Configuration& config){
  //---------------------------

  switch(config.heatmap_mode){
    case ope::heatmap::INTENSITY:{
      ope_heatmap->heatmap_intensity(entity, config.intensity_diviser);
      break;
    }
    case ope::heatmap::INTENSITY_COR:{
      ope_heatmap->heatmap_intensity_cor(entity);
      break;
    }
    case ope::heatmap::INTENSITY_CAL:{
      ope_heatmap->heatmap_intensity_cal(entity);
      break;
    }
    case ope::heatmap::INCIDENCE_ANGLE:{
      ope_heatmap->heatmap_incidence_angle(entity);
      break;
    }
    case ope::heatmap::HEIGHT:{
      ope_heatmap->heatmap_height(entity, config.heatmap_range_height);
      break;
    }
    case ope::heatmap::RANGE:{
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
  std::vector<glm::vec3>& colormap = ope::colormap::viridis_long;

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
