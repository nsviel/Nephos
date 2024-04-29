#pragma once

#include <Scene/src/Base/Glyph.h>


namespace glyph::grid{

class Mesh : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Mesh(eng::Node* node_engine);
  ~Mesh();

public:
  //Main function
  void create();

  //Subfunction
  void construct(int nb_cell);
  void construct_mesh(int nb_cell);
  void construct_submesh(int nb_cell);

private:
  vec4 color_mesh;
  vec4 color_submesh;
  int nb_subcell;
};

}
