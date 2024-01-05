#pragma once

#include <Engine/Base/Source.h>


namespace glyph::world{

class Axis : public glyph::base::Source
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  //Main function
  eng::structure::Glyph* create();
  void update();

private:
};

}
