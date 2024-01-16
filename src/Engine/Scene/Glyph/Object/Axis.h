#pragma once

#include <Engine/Entity/Base_glyph.h>

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
  void create();
  void update_glyph(eng::data::Entity* entity);

  //Subfunctions
  void construct();

private:
  eng::ope::Transformation* ope_transform;

  bool is_visible;
};

}
