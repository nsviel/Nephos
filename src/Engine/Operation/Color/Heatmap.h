#pragma once

#include <Engine/Operation/Namespace.h>

#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace glm;


namespace eng::ope{

class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap();
  ~Heatmap();

public:

private:
  eng::ope::Colormap* colormapManager;

  vec2 range_norm;
  vec2 range_height;
  vec2 range_intensity;
  bool is_normalization;
  int heatmap_mode;
};

}
