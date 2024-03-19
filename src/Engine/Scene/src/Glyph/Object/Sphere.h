#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::scene{

class Sphere : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Sphere(eng::Node* engine);
  ~Sphere();

public:
  //Main function
  void create();
  void update_glyph();

  //Subfunction
  void construct();

private:
};

}
