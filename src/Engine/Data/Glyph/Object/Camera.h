#pragma once

#include <Engine/Base/Source.h>


namespace glyph::object{

class Camera : public glyph::base::Source
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
