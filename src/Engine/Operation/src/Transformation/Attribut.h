#pragma once

#include <Utility/Specific/common.h>


namespace eng::ope{

class Attribut
{
public:
  // Constructor / Destructor
  Attribut();
  ~Attribut();

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
