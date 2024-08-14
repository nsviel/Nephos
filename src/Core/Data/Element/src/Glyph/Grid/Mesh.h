#pragma once

#include <Element/src/Base/Glyph.h>
#include <Element/src/Glyph/Grid/Structure.h>


namespace dat::glyph::grid{

class Mesh : public dat::base::Glyph, public dat::glyph::grid::Structure
{
public:
  //Constructor / Destructor
  Mesh();
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
