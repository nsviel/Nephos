#pragma once

#include <Data/src/Base/Glyph.h>
#include <Data/src/Glyph/Grid/Structure.h>

namespace eng{class Node;}
namespace dat::element{class Entity;}
namespace dat{class Glyph;}
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
  eng::Node* node_engine;
  dat::element::Entity* dat_entity;
  dat::Glyph* dat_glyph;

  int nb_cell;
};

}
