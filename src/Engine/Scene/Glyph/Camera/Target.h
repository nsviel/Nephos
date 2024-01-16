#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::camera{

class Target : public eng::base::Glyph
{
public:
  //Constructor / Destructor
  Target(Engine* engine);
  ~Target();

public:
  void create();
  void update_glyph(eng::base::Entity* entity);
  void construct(eng::base::Object* object);

private:
  float scale;
};

}
