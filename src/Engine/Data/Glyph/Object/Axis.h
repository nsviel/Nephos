#pragma once

#include <Engine/Base/Base_glyph.h>

#include <Engine/Operation/Transformation/Transformation.h>


namespace glyph::object{

class Axis : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  //Main function
  void create(eng::data::Object* object);
  void update(eng::data::Object* object);

  //Subfunctions
  void construct(eng::data::Object* axis);

private:
  eng::ope::Transformation* ope_transform;

  bool is_visible;
};

}
