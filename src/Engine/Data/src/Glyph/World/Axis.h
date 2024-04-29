#pragma once

#include <Data/base/Glyph.h>


namespace dat::glyph::world{

class Axis : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Axis(eng::Node* node_engine);
  ~Axis();

public:
  //Main function
  void create();

  //Subfunction
  void construct();

private:
};

}
