#pragma once

#include <Utility/Base/Namespace.h>
#include <Utility/Base/Namespace.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace glm;


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
