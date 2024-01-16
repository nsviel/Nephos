#pragma once

#include <Engine/Base/Entity/Base_glyph.h>


namespace glyph::camera{

class Camera : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Camera();
  ~Camera();

public:
  void create();
  void update_glyph(eng::data::Entity* entity);

private:

};

}
