#pragma once

#include <Engine/Operation/Namespace.h>
#include <Utility/Base/Entity/Glyph.h>


namespace glyph::object{

class Tree : public eng::base::Glyph
{
public:
  //Constructor / Destructor
  Tree(Engine* engine);
  ~Tree();

public:
  //Main function
  void create();
  void update_glyph(eng::base::Entity* entity);

  inline bool* get_visibility(){return &is_visible;}
  inline int* get_level(){return &level;}

private:
  eng::ope::Octree* octreeManager;
  int level;
};

}
