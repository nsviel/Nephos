#pragma once

#include <Engine/Base/Namespace.h>
#include <UTL_base/Struct_object.h>
#include <UTL_base/Struct_set.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace glm;


class Attribut
{
public:
  // Constructor / Destructor
  Attribut();
  ~Attribut();

public:
  //Main functions
  void compute_MinMax(eng::structure::Object* object);
  void set_visibility(data::Set* set, bool visibility);

private:
};
