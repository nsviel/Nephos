#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::object{

class Camera : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Camera();
  ~Camera();

public:
  void create();
  void update(eng::data::Object* object);

private:

};

}
