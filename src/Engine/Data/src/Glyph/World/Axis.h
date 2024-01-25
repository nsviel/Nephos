#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::world{

class Axis : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Axis(eng::Engine* engine);
  ~Axis();

public:
  //Main function
  void create();
  void update_glyph();

private:
};

}
