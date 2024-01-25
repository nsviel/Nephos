#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::camera{

class Camera : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Camera(eng::Engine* engine);
  ~Camera();

public:
  void create();
  void update_glyph(utl::type::Entity* entity);

private:

};

}
