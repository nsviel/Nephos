#include "Heatmap.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>


namespace ope::color{

//Constructor / destructor
Heatmap::Heatmap(){
  //---------------------------

  this->ope_location = new ope::attribut::Location();
  this->utl_attribut = new utl::base::Attribut();

  this->is_normalization = false;
  this->range_norm = glm::vec2(0.0f, 1.0f);
  this->range = glm::vec2(-1.0f, 2.0f);
  this->range_intensity = glm::vec2(0.0f, 1.0f);

  //---------------------------
}
Heatmap::~Heatmap(){}

//Main function
void Heatmap::heatmap_intensity(dat::base::Entity* entity, int diviser){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Prepare data
  std::vector<float>& vec_I = utl_attribut->get_attribut_data(data, "I");
  std::vector<float> Is = vec_I;
  math::divise(Is, diviser);
  math::normalize(Is, range_intensity);

  //Compute heatmap
  this->compute_heatmap(Is, data->rgba);

  //---------------------------
}
void Heatmap::heatmap_intensity_cor(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Prepare data
  std::vector<float>& vec_Icor = utl_attribut->get_attribut_data(data, "I_cor");
  std::vector<float> Is = vec_Icor;
  math::normalize(Is, range_intensity);

  //Compute heatmap
  this->compute_heatmap(Is, data->rgba);

  //---------------------------
}
void Heatmap::heatmap_intensity_cal(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Prepare data
  std::vector<float>& vec_Ical = utl_attribut->get_attribut_data(data, "I_cal");
  std::vector<float> Is = vec_Ical;
  math::normalize(Is, range_intensity);

  //Compute heatmap
  this->compute_heatmap(Is, data->rgba);

  //---------------------------
}
void Heatmap::heatmap_incidence_angle(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Prepare data
  std::vector<float>& vec_It = utl_attribut->get_attribut_data(data, "It");
  std::vector<float> It = vec_It;
  math::normalize(It, glm::vec2(0, 90));

  //Compute heatmap
  this->compute_heatmap(It, data->rgba);

  //---------------------------
}
void Heatmap::heatmap_height(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Prepare data
  std::vector<float> z_vec;
  ope_location->retrieve_z_vector(entity, z_vec);
  math::normalize(z_vec, range);

  //Compute heatmap
  this->compute_heatmap(z_vec, data->rgba);

  //---------------------------
}
void Heatmap::heatmap_height(dat::base::Entity* entity, glm::vec2 range){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Prepare data
  std::vector<float> z_vec;
  ope_location->retrieve_z_vector(entity, z_vec);
  math::normalize(z_vec, range);

  //Compute heatmap
  this->compute_heatmap(z_vec, data->rgba);

  //---------------------------
}
void Heatmap::heatmap_range(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Prepare data
  std::vector<float>& R_data = utl_attribut->get_attribut_data(data, "R");
  if(R_data.size() == 0) return;

  std::vector<float> R = R_data;
  math::normalize(R, glm::vec2(0, 10));

  //Compute heatmap
  this->compute_heatmap(R, data->rgba);

  //---------------------------
}

//Processing functions
void Heatmap::compute_heatmap(std::vector<float>& v_in, std::vector<glm::vec4>& rgba){
  if(v_in.size() == 0) return;
  //---------------------------

  //Normalization of the input vector
  if(is_normalization){
    math::normalize(v_in, -1);
  }

  //Compute heatmap from input vector
  std::vector<glm::vec3>& colormap = ope::colormap::viridis_long;
  const size_t colormap_size = colormap.size();

  #pragma omp parallel for
  for(int i=0; i<rgba.size(); i++){
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    if(v_in[i] != -1){
      float value = v_in[i] * (colormap_size - 1);        // Will multiply value by 3.
      float idx1  = floor(value);                  // Our desired color will be after this index.
      float idx2  = idx1 + 1;                        // ... and before this index (inclusive).
      float fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).

      float red   = ((colormap)[idx2][0] - (colormap)[idx1][0]) * fractBetween + (colormap)[idx1][0];
      float green = ((colormap)[idx2][1] - (colormap)[idx1][1]) * fractBetween + (colormap)[idx1][1];
      float blue  = ((colormap)[idx2][2] - (colormap)[idx1][2]) * fractBetween + (colormap)[idx1][2];

      color = glm::vec4(red, green, blue, 1.0f);
    }

    rgba[i] = color;
  }

  //---------------------------
}

}
