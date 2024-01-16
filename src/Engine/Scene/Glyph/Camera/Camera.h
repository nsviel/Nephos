#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::camera{

class Camera : public eng::base::Glyph
{
public:
  //Constructor / Destructor
  Camera(Engine* engine);
  ~Camera();

public:
  void create();
  void update_glyph(eng::base::Entity* entity);

private:

};

}
