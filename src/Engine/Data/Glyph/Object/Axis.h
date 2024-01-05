#pragma once

#include <Engine/Base/Source.h>

#include <Engine/Operation/Transformation/Transformation.h>


namespace glyph::object{

class Axis : public glyph::base::Source
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
