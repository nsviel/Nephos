#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::world{

class Axis : public eng::base::Glyph
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
