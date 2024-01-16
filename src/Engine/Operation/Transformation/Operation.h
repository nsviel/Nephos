#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace glm;


namespace eng::ope{

class Operation
{
public:
  // Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Main functions
  void center_object(eng::data::Object* object);
  void elevate_object(eng::data::Object* object);

private:
  eng::ope::Transformation* ope_transform;
  eng::ope::Attribut* ope_attribut;
};

}
