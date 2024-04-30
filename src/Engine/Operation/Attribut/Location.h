#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace ope::attribut{

class Location
{
public:
  // Constructor / Destructor
  Location();
  ~Location();

public:
  //Main functions
  glm::vec3 compute_centroid(dat::base::Set* set);
  glm::vec3 compute_centroid(dat::base::Entity* entity);
  void compute_MinMax(dat::base::Set* set);
  void compute_MinMax(dat::base::Entity* entity);
  void set_unicolor(dat::base::Entity* entity);
  void retrieve_z_vector(dat::base::Entity* entity, std::vector<float>& z_vec);

private:
};

}
