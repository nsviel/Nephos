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
  void create(eng::structure::Cloud* cloud);
  void update(eng::structure::Cloud* cloud);

private:

};

}
