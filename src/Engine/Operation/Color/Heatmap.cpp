#include "Heatmap.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>


namespace ope::color{

//Constructor / destructor
Heatmap::Heatmap(){
  //---------------------------

  this->ope_colormap = new ope::color::Colormap();
  this->ope_location = new ope::attribut::Location();

  this->is_normalization = false;
  this->range_norm = vec2(0.0f, 1.0f);
  this->range_height = vec2(-1.0f, 2.0f);
  this->range_intensity = vec2(0.0f, 1.0f);

  //---------------------------
}
Heatmap::~Heatmap(){
  //---------------------------

  delete ope_colormap;

  //---------------------------
}

//Main function
void Heatmap::heatmap_intensity(dat::base::Entity* entity, int diviser){
  utl::base::Data* data = entity->get_data();
  if(data->Is.size() == 0) return;
  //---------------------------

  //Prepare data
  std::vector<float> Is = data->Is;
  math::divise(Is, diviser);
  math::normalize(Is, range_intensity);

  //Compute heatmap
  this->compute_heatmap(Is, data->rgba);

  //---------------------------
}
void Heatmap::heatmap_height(dat::base::Entity* entity){
  utl::base::Data* data = entity->get_data();
  //---------------------------

  //Prepare data
  std::vector<float> z_vec;
  ope_location->retrieve_z_vector(entity, z_vec);
  math::normalize(z_vec, range_height);

  //Compute heatmap
  this->compute_heatmap(z_vec, data->rgba);

  //---------------------------
}
void Heatmap::heatmap_height(dat::base::Entity* entity, vec2 range){
  utl::base::Data* data = entity->get_data();
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
  utl::base::Data* data = entity->get_data();
  if(data->R.size() == 0) return;
  //---------------------------

  //Prepare data
  std::vector<float> R = data->R;
  math::normalize(R, vec2(0, 10));

  //Compute heatmap
  this->compute_heatmap(R, data->rgba);

  //---------------------------
}

//Processing functions
void Heatmap::compute_heatmap(std::vector<float>& v_in, std::vector<glm::vec4>& rgba){
  //---------------------------

  //Normalization of the input vector
  if(is_normalization){
    math::normalize(v_in, -1);
  }

  //Compute heatmap from input vector
  std::vector<vec3>& colormap = ope_colormap->get_colormap_selected();
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
