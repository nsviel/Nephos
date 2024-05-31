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
  void update_data();
  void visibility(bool value);

private:
  eng::Node* node_engine;
  dat::Entity* dat_entity;
  dat::Glyph* dat_glyph;
  dat::glyph::grid::Mesh* mesh;
  dat::glyph::grid::Axis* axis;
  dat::glyph::grid::Plane* plane;

  int nb_cell;
};

}
