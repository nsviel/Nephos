#pragma once

#include "../Base/Source.h"


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
};

}
