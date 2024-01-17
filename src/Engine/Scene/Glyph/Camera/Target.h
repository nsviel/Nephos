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
  void update_glyph(utl::type::Entity* entity);
  void construct(utl::type::Data* object);

private:
  float scale;
};

}
