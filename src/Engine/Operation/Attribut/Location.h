#pragma once

#include <Utility/Specific/Common.h>


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
  vec3 compute_centroid(utl::type::Entity* entity);
  void compute_MinMax(utl::type::Set* set);
  void compute_MinMax(utl::type::Entity* entity);
  void set_unicolor(utl::type::Entity* entity);
  void retrieve_z_vector(utl::type::Entity* entity, vector<float>& z_vec);

private:
};

}
