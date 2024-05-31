#pragma once

#include <Data/src/Glyph/Grid/Grid.h>


namespace dat::glyph::grid{

class Mesh : public dat::glyph::grid::Grid
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
  glm::vec4 color_mesh;
  glm::vec4 color_submesh;
  int nb_subcell;
};

}
