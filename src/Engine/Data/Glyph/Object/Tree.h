#pragma once

#include <Engine/Operation/Namespace.h>
#include <Engine/Base/Base_glyph.h>


namespace glyph::object{

class Tree : public eng::base::Glyph
{
public:
  //Constructor / Destructor
  Tree();
  ~Tree();

public:
  eng::structure::Glyph* create(eng::structure::Object* object);
  void update_tree(eng::structure::Object* object, eng::structure::Glyph* glyph);

  inline bool* get_visibility(){return &is_visible;}
  inline int* get_tree_level(){return &tree_level;}

private:
  eng::ope::Octree* octreeManager;
  bool is_visible;
  vec4 tree_color;
  int tree_level;
};

}
