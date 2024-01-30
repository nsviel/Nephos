#pragma once

#include <Utility/Specific/common.h>



namespace glyph::object{

class AABB : public utl::entity::Glyph
{
public:
  AABB(eng::Node* engine);
  ~AABB();

public:
  //Main function
  void create();
  void update_glyph(utl::type::Pose* pose);

  //Subfunction
  vector<vec3> build_box(vec3 min, vec3 max);

private:
  vec4 color;
};

}
