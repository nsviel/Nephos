#pragma once

#include <Utility/Base/Entity/Glyph.h>

#include <Engine/Operation/src/Transformation/Transformation.h>


namespace glyph::object{

class Axis : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Axis(eng::Node* node_engine);
  ~Axis();

public:
  //Main function
  void create();
  void update_pose(utl::type::Entity* entity);

  //Subfunctions
  void construct();

private:
  ope::Transformation* ope_transform;

  bool is_visible;
};

}
