#include "Heatmap.h"

#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::atr{

//Constructor / Destructor
Heatmap::Heatmap(dat::atr::Node* node_attribut){
  //---------------------------

  this->atr_struct = node_attribut->get_atr_struct();
  this->atr_field = new dat::atr::field::Manager();

  //---------------------------
}
Heatmap::~Heatmap(){}

//Main function
void Heatmap::colorization_heatmap(dat::base::Entity& entity){
  utl::base::Data& data = *entity.data;
  //---------------------------

  //Retrieve field
  std::vector<float>& vec_field = atr_field->get_field_data(data, atr_struct->color.field);
  std::vector<float> field = vec_field;

  //Normalization
  math::normalize(field, atr_struct->color.range, glm::vec2(0, 1));

  //Set to color
  std::unique_lock<std::mutex> lock(data.mutex);
  this->compute_heatmap(field, data.rgba);

  //---------------------------
}

//Subfunction
void Heatmap::compute_heatmap(std::vector<float>& v_in, std::vector<glm::vec4>& rgba){
  if(v_in.size() == 0) return;
  //---------------------------

  //Normalization of the input vector
  math::normalize(v_in, -1);

  //Compute heatmap from input vector
  std::vector<glm::vec3>& colormap = utl::colormap::viridis_long;
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
