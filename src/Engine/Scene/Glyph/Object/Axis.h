#pragma once

#include <Utility/Base/Entity/Glyph.h>

#include <Engine/Operation/Transformation/Transformation.h>


namespace glyph::object{

class Axis : public eng::base::Glyph
{
public:
  //Constructor / Destructor
  Axis(Engine* engine);
  ~Axis();

public:
  //Main function
  void create();
  void update_glyph(eng::base::Entity* entity);

  //Subfunctions
  void construct();

private:
  eng::ope::Transformation* ope_transform;

  bool is_visible;
};

}
