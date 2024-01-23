#pragma once

#include <Engine/Operation/src/Namespace.h>

#include <Utility/Specific/common.h>


namespace ope::src{

class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap();
  ~Heatmap();

  //Main function
  vector<vec4> heatmap_intensity(utl::entity::Object* object, int diviser);
  vector<vec4> heatmap_height(utl::entity::Object* object);
  vector<vec4> heatmap_height(utl::entity::Object* object, vec2 range);
  vector<vec4> heatmap_range(utl::entity::Object* object);
  
  //Heatmap functions
  void compute_heatmap(vector<float>& v_in, int size);
  void heatmap_set(utl::entity::Object* object, vector<float>& v_in);

  inline vec2* get_range_height(){return &range_height;}

private:
  ope::src::Colormap* colormapManager;
  ope::src::Attribut* attribManager;

  vector<vec4> heatmap;
  vec2 range_norm;
  vec2 range_height;
  vec2 range_intensity;
  bool is_normalization;
};

}
