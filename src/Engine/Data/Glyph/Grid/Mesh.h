#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::grid{

class Mesh : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Mesh();
  ~Mesh();

public:
  //Main function
  void create();
  void update();

  //Subfunction
  void construct_mesh();
  void construct_submesh();

private:
  vec4 color_mesh;
  vec4 color_submesh;
  int nb_cell;
  int nb_subcell;
};

}
