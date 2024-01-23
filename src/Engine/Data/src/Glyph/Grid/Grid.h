#pragma once

#include <Utility/Base/Entity/Glyph.h>
#include <Engine/Data/src/Glyph/Grid/Namespace.h>

namespace glyph::grid{


class Grid : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Grid(Engine* engine);
  ~Grid();

public:
  //Main function
  void create();
  void update_glyph();
  void insert_object_from_glyph(utl::entity::Glyph* glyph);

private:
  glyph::grid::Mesh* mesh;
  glyph::grid::Axis* axis;
  glyph::grid::Plane* plane;

  int nb_cell;
};

}
