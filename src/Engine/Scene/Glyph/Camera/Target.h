#pragma once

#include <Engine/Base/Entity/Glyph.h>


namespace glyph::camera{

class Target : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Target(Engine* engine);
  ~Target();

public:
  void create();
  void update_glyph(eng::data::Entity* entity);
  void construct(eng::data::Object* object);

private:
  float scale;
};

}
