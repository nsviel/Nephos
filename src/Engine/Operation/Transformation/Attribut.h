#pragma once

#include <Engine/Base/Namespace.h>
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
  void compute_MinMax(eng::structure::Object* object);
  void set_visibility(eng::structure::Set* set, bool visibility);
  void set_unicolor(eng::structure::Object* object);
  vector<float> get_z_vector(vector<vec3>& xyz);

private:
};

}
