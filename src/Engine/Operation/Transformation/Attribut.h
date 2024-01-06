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
  void compute_MinMax(eng::data::Object* object);
  void set_visibility(eng::data::Set* set, bool visibility);
  void set_unicolor(eng::data::Object* object);
  vector<float> retrieve_z_vector(eng::data::Object* object);

private:
};

}
