#pragma once

#include <Base/Entity/Glyph.h>


namespace dat::glyph::world{

class Axis : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  //Main function
  void create();

  //Subfunction
  void construct();

private:
};

}
