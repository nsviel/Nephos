#pragma once

#include <Data/src/Base/Glyph.h>

namespace eng{class Node;}
namespace dat{class Entity;}
namespace dat{class Glyph;}
namespace dat::glyph::grid{class Mesh;}
namespace dat::glyph::grid{class Axis;}
namespace dat::glyph::grid{class Plane;}


namespace dat::glyph::grid{

class Grid : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Grid(eng::Node* node_engine);
  ~Grid();

public:
  //Main function
  void create();
  virtual void construct(int nb_cell);

private:
  eng::Node* node_engine;
  dat::Entity* dat_entity;
  dat::Glyph* dat_glyph;

  int nb_cell;
};

}
