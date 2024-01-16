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
  void update_glyph(int nb_cell);

  //Subfunction
  void construct_mesh(int nb_cell);
  void construct_submesh(int nb_cell);

private:
  vec4 color_mesh;
  vec4 color_submesh;
  int nb_subcell;
};

}
