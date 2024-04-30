#pragma once

#include <Utility/Specific/Common.h>

namespace utl::entity{class Object;}


namespace ope::tree{
class Root;
class Cube;

class Octree
{
public:
  //Constructor / Destructor
  Octree();
  ~Octree();

public:
  void create_octree(utl::entity::Object* object);
  void create_octree(utl::entity::Object* object, int level);
  void remove_octree(ope::tree::Root* root);

  //Sub functions
  void remove_cube(ope::tree::Cube* cube);
  void build_root(utl::entity::Object* object);
  void build_octree(ope::tree::Cube* cube_parent);
  vector<vec3> compute_cube_location(vec3 min, vec3 max);
  vector<vec4> compute_cube_color(int size);
  vector<vec4> compute_cube_color(int size, vec4 rgb);
  void compute_cube_division(ope::tree::Cube* cube);
  vector<int> compute_idx_from_point(vec3 min, vec3 max, ope::tree::Cube* cube_parent);
  bool is_at_least_one_value(vector<int> vec);

private:
  ope::tree::Root* root;
  vec4 octree_color;
  bool with_rdm_color;
  int octree_time;
  int nb_level;
};

}
