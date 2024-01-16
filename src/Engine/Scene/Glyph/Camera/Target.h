#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::camera{

class Target : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Target();
  ~Target();

public:
  void create();
  void update_glyph(eng::data::Entity* entity);
  void construct(eng::data::Object* object);

private:
  float scale;
};

}
