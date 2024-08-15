#include "Color.h"

#include <Utility/Function/Attribut/Operation.h>
#include <Operation/Namespace.h>
#include <Data/Namespace.h>


namespace ope::attribut{

//Constructor / Destructor
Color::Color(ope::Node* node_operation){
  //---------------------------

  this->ope_struct = node_operation->get_ope_struct();
  this->utl_attribut = new utl::base::Attribut();

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::make_colorization(utl::base::Element* element){
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    this->make_colorization(set);
  }else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    this->make_colorization(entity);
  }

  //---------------------------
}
void Color::make_colorization(dat::base::Set* set){
  //---------------------------

  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    this->make_colorization(entity);
  }

  //---------------------------
}
void Color::make_colorization(dat::base::Entity* entity){
  //---------------------------

  //Check color vector
  if(entity->data.rgba.size() != entity->data.xyz.size()){
    entity->data.rgba = std::vector<glm::vec4>(entity->data.xyz.size(), glm::vec4(0.0f));
  }

  //Apply colorization
  switch(ope_struct->attribut.color.mode){
    case ope::color::RGB:{
      this->colorization_rgb(entity);
      break;
    }
    case ope::color::UNICOLOR:{
      this->colorization_unicolor(entity);
      break;
    }
    case ope::color::NORMAL:{
      this->colorization_normal(entity);
      break;
    }
    case ope::color::FIELD:{
      this->colorization_field(entity);
      break;
    }
    case ope::color::STRUCTURE:{
      this->colorization_structure(entity);
      break;
    }
    case ope::color::HEATMAP:{
      this->colorization_heatmap(entity);
      break;
    }
  }

  //Mark entity as need update
  entity->data.is_updated = true;

  //---------------------------
}

//Subfunction
void Color::colorization_rgb(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  for(int i=0; i<data->rgb.size(); i++){
    glm::vec3& rgb = data->rgb[i];
    data->rgba[i] = glm::vec4(rgb.x, rgb.y, rgb.z, 1);
  }

  //---------------------------
}
void Color::colorization_unicolor(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  data->rgba = std::vector<glm::vec4>(data->rgba.size(), ope_struct->attribut.color.unicolor);

  //---------------------------
}
void Color::colorization_normal(dat::base::Entity* entity){
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
void Color::colorization_field(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Normalization
  std::vector<float>& vec_field = utl_attribut->get_field_data(data, ope_struct->attribut.color.field);
  std::vector<float> field = vec_field;
  math::normalize(field, ope_struct->attribut.color.range, glm::vec2(0, 1));

  //Set to color
  for(int i=0; i<field.size(); i++){
    float& value = field[i];
    data->rgba[i] = glm::vec4(value, value, value, 1);
  }

  //---------------------------
}
void Color::colorization_structure(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  // Define a color gradient from red to blue
  std::vector<glm::vec3>& colormap = utl::colormap::viridis_long;

  // Calculate the step size for color interpolation along rows and columns
  float row_step = 1.0f / (data->height - 1);
  float col_step = 1.0f / (data->width - 1);

  // Loop through the points and assign colors
  int index = 0;
  for(int i = 0; i < data->height; ++i){
    for(int j = 0; j < data->width; ++j){
      // Calculate the index in the colormap based on the normalized position
      int colormap_index = row_step * i * (colormap.size() - 1);

      // Interpolate between colors based on the index along rows
      const glm::vec3& color1_row = colormap[colormap_index];
      const glm::vec3& color2_row = colormap[colormap_index + 1];
      float t_row = static_cast<float>(i % data->height) / (data->height - 1); // Interpolation factor along rows
      glm::vec3 interpolated_color_row = (1.0f - t_row) * color1_row + t_row * color2_row;

      // Interpolate between colors based on the index along columns
      const glm::vec3& color1_col = colormap[colormap_index];
      const glm::vec3& color2_col = colormap[colormap_index + 1];
      float t_col = static_cast<float>(j % data->width) / (data->width - 1); // Interpolation factor along columns
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
void Color::colorization_heatmap(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Normalization
  std::vector<float>& vec_field = utl_attribut->get_field_data(data, ope_struct->attribut.color.field);
  std::vector<float> field = vec_field;
  math::normalize(field, ope_struct->attribut.color.range, glm::vec2(0, 1));

  //Set to color
  utl::attribut::compute_heatmap(field, data->rgba);

  //---------------------------
}

}
