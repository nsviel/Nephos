#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::camera{

class Target : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Target(eng::Node* engine);
  ~Target();

public:
  void create();
  void update_glyph(utl::type::Entity* entity);
  void construct(utl::type::Data* object);

private:
  float scale;
};

}
