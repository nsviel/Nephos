#pragma once

#include <Engine/Base/Entity/Base_glyph.h>


namespace glyph::world{

class Axis : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  //Main function
  void create();
  void update_glyph();

private:
};

}
