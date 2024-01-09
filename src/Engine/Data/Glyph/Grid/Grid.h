#pragma once

#include <Engine/Base/Base_glyph.h>
#include <Engine/Data/Glyph/Grid/Namespace.h>

class VK_engine;

namespace glyph::grid{


class Grid : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Grid(VK_engine* vk_engine);
  ~Grid();

public:
  //Main function
  void create();
  void update();

private:
  VK_engine* vk_engine;
  glyph::grid::Mesh mesh;
  glyph::grid::Axis axis;
  glyph::grid::Plane plane;

  int nb_cell;
};

}
