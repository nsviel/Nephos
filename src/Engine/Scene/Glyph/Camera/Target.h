#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::camera{

class Target : public entity::Glyph
{
public:
  //Constructor / Destructor
  Target(Engine* engine);
  ~Target();

public:
  void create();
  void update_glyph(entity::Entity* entity);
  void construct(utl::base::Data* object);

private:
  float scale;
};

}
