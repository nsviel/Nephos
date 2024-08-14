#pragma once

#include <Element/src/Base/Glyph.h>
#include <Element/src/Glyph/Grid/Structure.h>

namespace core{class Node;}
namespace dat::elm{class Entity;}
namespace dat::elm{class Glyph;}
namespace dat::glyph::grid{class Mesh;}
namespace dat::glyph::grid{class Axis;}
namespace dat::glyph::grid{class Plane;}
namespace dat::glyph::grid{class Structure;}


namespace dat::glyph::grid{

class Grid : public dat::base::Glyph, public dat::glyph::grid::Structure
{
public:
  //Constructor / Destructor
  Grid();
  ~Grid();

public:
  //Main function
  void create();
  void construct(int nb_cell);

private:
  core::Node* node_core;
  dat::elm::Entity* dat_entity;
  dat::elm::Glyph* dat_glyph;

  int nb_cell;
};

}
