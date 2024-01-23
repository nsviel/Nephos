#include "Heatmap.h"

#include <Utility/Function/Math/fct_math.h>


namespace eng::ope{

//Constructor / destructor
Heatmap::Heatmap(){
  //---------------------------

  this->colormapManager = new eng::ope::Colormap();
  this->attribManager = new eng::ope::Attribut();

  this->is_normalization = true;
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
vector<vec4> Heatmap::heatmap_intensity(utl::entity::Object* object, int diviser){
  //---------------------------

  vector<float> I_divided = math::divise(object->data->Is, diviser);
  vector<float> I_norm = math::fct_normalize(I_divided, range_intensity);
  this->compute_heatmap(I_norm, object->data->xyz.size());

  //---------------------------
  return heatmap;
}
vector<vec4> Heatmap::heatmap_height(utl::entity::Object* object){
  //---------------------------

  vector<float> z_vec = attribManager->retrieve_z_vector(object);
  vector<float> z_vec_norm = math::fct_normalize(z_vec, range_height);
  this->compute_heatmap(z_vec_norm, object->data->xyz.size());

  //---------------------------
  return heatmap;
}
vector<vec4> Heatmap::heatmap_height(utl::entity::Object* object, vec2 range){
  //---------------------------

  vector<float> z_vec = attribManager->retrieve_z_vector(object);
  vector<float> z_vec_norm = math::fct_normalize(z_vec, range);
  this->compute_heatmap(z_vec_norm, object->data->xyz.size());

  //---------------------------
  return heatmap;
}
vector<vec4> Heatmap::heatmap_range(utl::entity::Object* object){
  //---------------------------

  vector<float>& dist = object->data->R;
  vector<float> dist_norm = math::fct_normalize(dist);
  this->compute_heatmap(dist_norm, object->data->xyz.size());

  //---------------------------
  return heatmap;
}

//Processing functions
void Heatmap::compute_heatmap(vector<float>& v_in, int size){
  //---------------------------

  heatmap.clear();
  heatmap.reserve(size);

  //Normalization of the input vector
  vector<float> v_norm;
  if(is_normalization){
    v_norm = math::fct_normalize(v_in, -1);
  }else{
    v_norm = v_in;
  }

  //Compute heatmap from input vector
  vec4 color;
  for(int i=0; i<size; i++){
    if(v_in[i] != -1 && isnan(v_norm[i]) == false){
      vector<vec3>* colormap = colormapManager->get_colormap_selected();

      float value = v_norm[i] * (colormap->size()-1);        // Will multiply value by 3.
      float idx1  = floor(value);                  // Our desired color will be after this index.
      float idx2  = idx1 + 1;                        // ... and before this index (inclusive).
      float fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).

      float red   = ((*colormap)[idx2][0] - (*colormap)[idx1][0]) * fractBetween + (*colormap)[idx1][0];
      float green = ((*colormap)[idx2][1] - (*colormap)[idx1][1]) * fractBetween + (*colormap)[idx1][1];
      float blue  = ((*colormap)[idx2][2] - (*colormap)[idx1][2]) * fractBetween + (*colormap)[idx1][2];

      color = vec4(red, green, blue, 1.0f);
    }
    else{
      color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    heatmap.push_back(color);
  }

  //---------------------------
}
void Heatmap::heatmap_set(utl::entity::Object* object, vector<float>& v_in){
  vector<vec4>& RGB = object->data->rgb;
  //---------------------------

  //Normalization of the input vector
  vector<float> v_norm;
  if(is_normalization){
    v_norm = math::fct_normalize(v_in, -1);
  }else{
    v_norm = v_in;
  }

  //Compute heatmap from input vector
  for(int i=0; i<RGB.size(); i++){
    if(v_in[i] != -1 && isnan(v_norm[i]) == false){
      vector<vec3>* colormap = colormapManager->get_colormap_selected();

      float value = v_norm[i] * (colormap->size()-1);        // Will multiply value by 3.
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
