#pragma once

#include <Engine/Operation/Namespace.h>
#include <Utility/Base/Namespace.h>
#include <Utility/Specific/common.h>


namespace eng::ope{

class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap();
  ~Heatmap();

  //Main function
  vector<vec4> heatmap_intensity(entity::Object* object, int diviser);
  vector<vec4> heatmap_height(entity::Object* object);
  vector<vec4> heatmap_height(entity::Object* object, vec2 range);
  vector<vec4> heatmap_range(entity::Object* object);
  
  //Heatmap functions
  void compute_heatmap(vector<float>& v_in, int size);
  void heatmap_set(entity::Object* object, vector<float>& v_in);

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
