#pragma once

#include <Engine/Base/Entity/Glyph.h>


namespace glyph::camera{

class Camera : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Camera(Engine* engine);
  ~Camera();

public:
  void create();
  void update_glyph(eng::data::Entity* entity);

private:

};

}
