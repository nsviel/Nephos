#include "Heatmap.h"

#include <Utility/Function/Math/Math.h>
#include <Engine/Operation/Namespace.h>


namespace eng::ope{

//Constructor / destructor
Heatmap::Heatmap(){
  //---------------------------

  this->colormapManager = new eng::ope::Colormap();
  this->attribManager = new eng::ope::Attribut();

  this->is_normalization = false;
  this->range_norm = vec2(0.0f, 1.0f);
  this->range_height = vec2(-1.0f, 2.0f);
  this->range_intensity = vec2(0.0f, 1.0f);

  //---------------------------
}
Heatmap::~Heatmap(){
  //---------------------------

  delete colormapManager;

  //---------------------------
}

//Main function
void Heatmap::heatmap_intensity(vector<vec4>& vec_rgba, utl::entity::Object* object, int diviser){
  //---------------------------

  //Prepare data
  vector<float> Is = object->data->Is;
  math::divise_vec(Is, diviser);
  math::Normalize(Is, range_intensity);

  //Compute heatmap
  vec_rgba = vector<vec4>(object->data->xyz.size());
  this->compute_heatmap(Is, vec_rgba);

  //---------------------------
}
void Heatmap::heatmap_height(vector<vec4>& vec_rgba, utl::entity::Object* object){
  //---------------------------

  //Prepare data
  vector<float> z_vec;
  attribManager->retrieve_z_vector(object, z_vec);
  math::Normalize(z_vec, range_height);

  //Compute heatmap
  vec_rgba = vector<vec4>(object->data->xyz.size());
  this->compute_heatmap(z_vec, vec_rgba);

  //---------------------------
}
void Heatmap::heatmap_height(vector<vec4>& vec_rgba, utl::entity::Object* object, vec2 range){
  //---------------------------

  //Prepare data
  vector<float> z_vec;
  attribManager->retrieve_z_vector(object, z_vec);
  math::Normalize(z_vec, range);

  //Compute heatmap
  vec_rgba = vector<vec4>(object->data->xyz.size());
  this->compute_heatmap(z_vec, vec_rgba);

  //---------------------------
}
void Heatmap::heatmap_range(vector<vec4>& vec_rgba, utl::entity::Object* object){
  //---------------------------

  //Prepare data
  vector<float> R = object->data->R;
  math::Normalize(R);

  //Compute heatmap
  vec_rgba = vector<vec4>(object->data->xyz.size());
  this->compute_heatmap(R, vec_rgba);

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
  vector<vec3>* colormap = colormapManager->get_colormap_selected();
  const size_t colormap_size = colormap->size();

  #pragma omp parallel for
  for(int i=0; i<heatmap.size(); i++){
    vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    if(v_in[i] != -1){
      float value = v_in[i] * (colormap_size - 1);        // Will multiply value by 3.
      float idx1  = floor(value);                  // Our desired color will be after this index.
      float idx2  = idx1 + 1;                        // ... and before this index (inclusive).
      float fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).

      float red   = ((*colormap)[idx2][0] - (*colormap)[idx1][0]) * fractBetween + (*colormap)[idx1][0];
      float green = ((*colormap)[idx2][1] - (*colormap)[idx1][1]) * fractBetween + (*colormap)[idx1][1];
      float blue  = ((*colormap)[idx2][2] - (*colormap)[idx1][2]) * fractBetween + (*colormap)[idx1][2];

      color = vec4(red, green, blue, 1.0f);
    }

    heatmap[i] = color;
  }

  //---------------------------
}
void Heatmap::heatmap_set(utl::entity::Object* object, vector<float>& v_in){
  vector<vec4>& RGB = object->data->rgb;
  //---------------------------

  //Normalization of the input vector
  if(is_normalization){
    math::Normalize(v_in, -1);
  }

  //Compute heatmap from input vector
  for(int i=0; i<RGB.size(); i++){
    if(v_in[i] != -1 && isnan(v_in[i]) == false){
      vector<vec3>* colormap = colormapManager->get_colormap_selected();

      float value = v_in[i] * (colormap->size()-1);        // Will multiply value by 3.
      float idx1  = floor(value);                  // Our desired color will be after this index.
      float idx2  = idx1 + 1;                        // ... and before this index (inclusive).
      float fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).

      float red   = ((*colormap)[idx2][0] - (*colormap)[idx1][0]) * fractBetween + (*colormap)[idx1][0];
      float green = ((*colormap)[idx2][1] - (*colormap)[idx1][1]) * fractBetween + (*colormap)[idx1][1];
      float blue  = ((*colormap)[idx2][2] - (*colormap)[idx1][2]) * fractBetween + (*colormap)[idx1][2];

      RGB[i] = vec4(red, green, blue, 1.0f);
    }
    else{
      RGB[i] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
  }

  //---------------------------
}



}
