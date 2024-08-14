#pragma once

#include <Operation/Namespace.h>
#include <Element/src/Base/Glyph.h>


namespace dat::glyph::object{

class Axis : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  //Main function
  void create();
  void update_pose(dat::base::Entity* entity);

  //Subfunctions
  void construct();

private:
};

}
