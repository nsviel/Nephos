#pragma once

#include <Engine/Operation/src/Namespace.h>
#include <Utility/Base/Entity/Glyph.h>


namespace glyph::object{

class Tree : public entity::Glyph
{
public:
  //Constructor / Destructor
  Tree(Engine* engine);
  ~Tree();

public:
  //Main function
  void create();
  void update_glyph(utl::type::Data* data);

  inline bool* get_visibility(){return &is_visible;}
  inline int* get_level(){return &level;}

private:
  eng::ope::Octree* octreeManager;
  int level;
};

}
