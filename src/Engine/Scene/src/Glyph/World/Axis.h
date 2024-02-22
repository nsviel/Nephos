#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::world{

class Axis : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Axis(eng::Node* engine);
  ~Axis();

public:
  //Main function
  void create();
  void update_glyph();

  //Subfunction
  void construct();

private:
};

}
