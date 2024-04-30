#pragma once

#include <Operation/Namespace.h>
#include <Data/src/Base/Glyph.h>


namespace dat::glyph::object{

class Axis : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Axis(eng::Node* node_engine);
  ~Axis();

public:
  //Main function
  void create();
  void update_pose(dat::base::Entity* entity);

  //Subfunctions
  void construct();

private:
  ope::Transformation* ope_transform;

  bool is_visible;
};

}
