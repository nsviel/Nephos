#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace dat::base{class Object;}


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
  void create_octree(std::shared_ptr<dat::base::Object> object);
  void create_octree(std::shared_ptr<dat::base::Object> object, int level);
  void remove_octree(ope::tree::Root* root);

  //Sub functions
  void remove_cube(ope::tree::Cube* cube);
  void build_root(std::shared_ptr<dat::base::Object> object);
  void build_octree(ope::tree::Cube* cube_parent);
  std::vector<glm::vec3> compute_cube_location(glm::vec3 min, glm::vec3 max);
  std::vector<glm::vec4> compute_cube_color(int size);
  std::vector<glm::vec4> compute_cube_color(int size, glm::vec4 rgb);
  void compute_cube_division(ope::tree::Cube* cube);
  std::vector<int> compute_idx_from_point(glm::vec3 min, glm::vec3 max, ope::tree::Cube* cube_parent);
  bool is_at_least_one_value(std::vector<int> vec);

private:
  ope::tree::Root* root;
  glm::vec4 octree_color;
  bool with_rdm_color;
  int octree_time;
  int nb_level;
};

}
