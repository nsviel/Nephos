#pragma once

#include "../Base/Source.h"


namespace glyph::world{

class Axis : public glyph::base::Source
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  //Main function
  void create();
  void update();

private:
};

}
