#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::object{

class Camera : public eng::base::Glyph
{
public:
  //Constructor / Destructor
  Camera();
  ~Camera();

public:
  void create(eng::structure::Object* object);
  void update(eng::structure::Object* object);

private:

};

}
