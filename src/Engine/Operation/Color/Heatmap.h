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
  vector<vec4> retrieve_heatmap(eng::structure::Object* object);

  //Specific mode functions
  void mode_height(eng::structure::Object* object);
  void mode_intensity(eng::structure::Object* object);
  void mode_distance(eng::structure::Object* object);
  void mode_cosIt(eng::structure::Object* object);
  void mode_It(eng::structure::Object* object);

  //Heatmap functions
  void heatmap_set(eng::structure::Object* object, vector<float>& v_in);

private:
  eng::ope::Colormap* colormapManager;
  eng::ope::Attribut* attribManager;

  vector<vec4> heatmap;
  vec2 range_norm;
  vec2 range_height;
  vec2 range_intensity;
  bool is_normalization;
  int heatmap_mode;
};

}
