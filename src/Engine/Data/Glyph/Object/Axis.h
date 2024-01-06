#pragma once

#include <Engine/Base/Base_glyph.h>

#include <Engine/Operation/Transformation/Transformation.h>


namespace glyph::object{

class Axis : public eng::base::Glyph
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  void create(eng::structure::Object* object);
  void update(eng::structure::Object* object);

private:
  eng::ope::Transformation* ope_transform;

  bool is_visible;
};

}
