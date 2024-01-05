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
  void create(eng::structure::Cloud* cloud);
  void update(eng::structure::Cloud* cloud);

private:
  eng::ope::Transformation* ope_transform;

  bool is_visible;
};

}
