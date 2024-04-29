#pragma once

#include <Scene/src/Base/Glyph.h>


namespace glyph::object{

class Normal : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Normal(eng::Node* node_engine);
  ~Normal();

public:
  //Main function
  void create();
  void update_pose(utl::type::Entity* entity);
  void update_glyph(utl::type::Entity* entity);

  //Construct
  void construct(utl::type::Entity* entity);
  glm::vec4 generate_random();

  inline int* get_size(){return &size;}

private:
  bool visibility;
  vec4 color;
  int width;
  int size;
};

}
