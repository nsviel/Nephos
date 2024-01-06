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
  void create(eng::data::Object* object);
  void update(eng::data::Object* object);

private:

};

}
