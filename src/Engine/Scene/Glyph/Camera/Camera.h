#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::camera{

class Camera : public entity::Glyph
{
public:
  //Constructor / Destructor
  Camera(Engine* engine);
  ~Camera();

public:
  void create();
  void update_glyph(utl::type::Entity* entity);

private:

};

}
