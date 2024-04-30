#pragma once

#include <Utility/Specific/Common.h>

namespace utl::type{class Set;}
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
  vec3 compute_centroid(utl::type::Set* set);
  vec3 compute_centroid(dat::base::Entity* entity);
  void compute_MinMax(utl::type::Set* set);
  void compute_MinMax(dat::base::Entity* entity);
  void set_unicolor(dat::base::Entity* entity);
  void retrieve_z_vector(dat::base::Entity* entity, vector<float>& z_vec);

private:
};

}
