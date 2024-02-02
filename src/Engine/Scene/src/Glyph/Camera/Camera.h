#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::camera{

class Camera : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Camera(eng::Node* engine);
  ~Camera();

public:
  void create();

private:

};

}
