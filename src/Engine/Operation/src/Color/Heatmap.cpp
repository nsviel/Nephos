#include "Heatmap.h"

#include <Utility/Function/Math/Math.h>
#include <Operation/Namespace.h>


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
void Heatmap::heatmap_intensity(utl::type::Entity* entity, int diviser){
  utl::type::Data* data = entity->get_data();
  //---------------------------

  //Prepare data
  vector<float> Is = data->point.Is;
  math::divise_vec(Is, diviser);
  math::Normalize(Is, range_intensity);

  //Compute heatmap
  this->compute_heatmap(Is, data->point.rgb);

  //---------------------------
}
void Heatmap::heatmap_height(utl::type::Entity* entity){
  utl::type::Data* data = entity->get_data();
  //---------------------------

  //Prepare data
  vector<float> z_vec;
  ope_location->retrieve_z_vector(entity, z_vec);
  math::Normalize(z_vec, range_height);

  //Compute heatmap
  this->compute_heatmap(z_vec, data->point.rgb);

  //---------------------------
}
void Heatmap::heatmap_height(utl::type::Entity* entity, vec2 range){
  utl::type::Data* data = entity->get_data();
  //---------------------------

  //Prepare data
  vector<float> z_vec;
  ope_location->retrieve_z_vector(entity, z_vec);
  math::Normalize(z_vec, range);

  //Compute heatmap
  this->compute_heatmap(z_vec, data->point.rgb);

  //---------------------------
}
void Heatmap::heatmap_range(utl::type::Entity* entity){
  utl::type::Data* data = entity->get_data();
  //---------------------------

  //Prepare data
  vector<float> R = data->point.R;
  math::Normalize(R);

  //Compute heatmap
  this->compute_heatmap(R, data->point.rgb);

  //---------------------------
}

//Processing functions
void Heatmap::compute_heatmap(vector<float>& v_in, vector<vec4>& heatmap){
  //---------------------------

  //Normalization of the input vector
  if(is_normalization){
    math::Normalize(v_in, -1);
  }

  //Compute heatmap from input vector
  vector<vec3>& colormap = ope_colormap->get_colormap_selected();
  const size_t colormap_size = colormap.size();

  #pragma omp parallel for
  for(int i=0; i<heatmap.size(); i++){
    vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    if(v_in[i] != -1){
      float value = v_in[i] * (colormap_size - 1);        // Will multiply value by 3.
      float idx1  = floor(value);                  // Our desired color will be after this index.
      float idx2  = idx1 + 1;                        // ... and before this index (inclusive).
      float fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).

      float red   = ((colormap)[idx2][0] - (colormap)[idx1][0]) * fractBetween + (colormap)[idx1][0];
      float green = ((colormap)[idx2][1] - (colormap)[idx1][1]) * fractBetween + (colormap)[idx1][1];
      float blue  = ((colormap)[idx2][2] - (colormap)[idx1][2]) * fractBetween + (colormap)[idx1][2];

      color = vec4(red, green, blue, 1.0f);
    }

    heatmap[i] = color;
  }

  //---------------------------
}
void Heatmap::heatmap_set(utl::type::Entity* entity, vector<float>& v_in){
  utl::type::Data* data = entity->get_data();
  vector<vec4>& RGB = data->point.rgb;
  //---------------------------

  //Normalization of the input vector
  if(is_normalization){
    math::Normalize(v_in, -1);
  }

  //Compute heatmap from input vector
  for(int i=0; i<RGB.size(); i++){
    if(v_in[i] != -1 && isnan(v_in[i]) == false){
      vector<vec3>& colormap = ope_colormap->get_colormap_selected();

      float value = v_in[i] * (colormap.size()-1);        // Will multiply value by 3.
      float idx1  = floor(value);                  // Our desired color will be after this index.
      float idx2  = idx1 + 1;                        // ... and before this index (inclusive).
      float fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).

      float red   = ((colormap)[idx2][0] - (colormap)[idx1][0]) * fractBetween + (colormap)[idx1][0];
      float green = ((colormap)[idx2][1] - (colormap)[idx1][1]) * fractBetween + (colormap)[idx1][1];
      float blue  = ((colormap)[idx2][2] - (colormap)[idx1][2]) * fractBetween + (colormap)[idx1][2];

      RGB[i] = vec4(red, green, blue, 1.0f);
    }
    else{
      RGB[i] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
  }

  //---------------------------
}



}
