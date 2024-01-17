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
  void compute_MinMax(utl::type::Data* data);
  void set_unicolor(utl::type::Data* data);
  vector<float> retrieve_z_vector(utl::type::Data* data);

private:
};

}
