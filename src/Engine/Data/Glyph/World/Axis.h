#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::world{

class Axis : public entity::Glyph
{
public:
  //Constructor / Destructor
  Axis(Engine* engine);
  ~Axis();

public:
  //Main function
  void create();
  void update_glyph();

private:
};

}
