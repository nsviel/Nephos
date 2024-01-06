#pragma once

#include <Engine/Operation/Namespace.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>


namespace eng::ope{

class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap();
  ~Heatmap();

  //Main function
  vector<vec4> heatmap_intensity(eng::data::Object* object, int diviser);
  vector<vec4> heatmap_height(eng::data::Object* object);
  vector<vec4> heatmap_height(eng::data::Object* object, vec2 range);
  vector<vec4> heatmap_range(eng::data::Object* object);
  
  //Heatmap functions
  void compute_heatmap(vector<float>& v_in, int size);
  void heatmap_set(eng::data::Object* object, vector<float>& v_in);

  inline vec2* get_range_height(){return &range_height;}

private:
  eng::ope::Colormap* colormapManager;
  eng::ope::Attribut* attribManager;

  vector<vec4> heatmap;
  vec2 range_norm;
  vec2 range_height;
  vec2 range_intensity;
  bool is_normalization;
};

}
