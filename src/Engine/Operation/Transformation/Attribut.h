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
  void compute_MinMax(utl::type::Entity* entity);
  void set_unicolor(utl::type::Entity* entity);
  vector<float> retrieve_z_vector(utl::type::Entity* entity);

private:
};

}
