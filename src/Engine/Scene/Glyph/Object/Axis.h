#pragma once

#include <Engine/Base/Entity/Glyph.h>

#include <Engine/Operation/Transformation/Transformation.h>


namespace glyph::object{

class Axis : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Axis(Engine* engine);
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
