#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::grid{

class Mesh : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Mesh(Engine* engine);
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
