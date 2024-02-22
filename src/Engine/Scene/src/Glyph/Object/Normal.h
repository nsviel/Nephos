#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::object{

class Normal : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Normal(eng::Node* engine);
  ~Normal();

public:
  //Main function
  void create();
  void update_glyph(utl::type::Entity* entity);

  //Construct
  void construct(utl::type::Entity* entity);

  inline bool* get_visibility(){return &visibility;}
  inline int* get_size(){return &size;}

private:
  bool visibility;
  vec4 color;
  int width;
  int size;
};

}
