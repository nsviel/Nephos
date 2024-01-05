#pragma once

#include "../Base/Source.h"


namespace glyph::world{

class Grid : public glyph::base::Source
{
public:
  //Constructor / Destructor
  Grid();
  ~Grid();

public:
  //Main function
  void create();
  void update();

private:
  int nb_cell;
};

}
