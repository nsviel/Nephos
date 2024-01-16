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
  void compute_MinMax(eng::base::Object* object);
  void set_visibility(eng::base::Set* set, bool visibility);
  void set_unicolor(eng::base::Object* object);
  vector<float> retrieve_z_vector(eng::base::Object* object);

private:
};

}
