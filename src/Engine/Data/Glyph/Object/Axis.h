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
  void create(eng::data::Object* object);
  void update(eng::data::Object* object);

private:
  eng::ope::Transformation* ope_transform;

  bool is_visible;
};

}
