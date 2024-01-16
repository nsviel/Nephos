#pragma once

#include <Engine/Operation/Namespace.h>
#include <Engine/Base/Entity/Base_glyph.h>


namespace glyph::object{

class Tree : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Tree();
  ~Tree();

public:
  //Main function
  void create();
  void update_glyph(eng::data::Entity* entity);

  inline bool* get_visibility(){return &is_visible;}
  inline int* get_level(){return &level;}

private:
  eng::ope::Octree* octreeManager;
  int level;
};

}
