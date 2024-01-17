#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Operation/Namespace.h>


namespace eng::ope{

class Operation
{
public:
  // Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Main functions
  void center_object(utl::type::Data* data);
  void elevate_object(utl::type::Data* data);
  void make_rotation_X_90d(utl::type::Data* data, int value);

private:
  eng::ope::Transformation* ope_transform;
  eng::ope::Attribut* ope_attribut;
};

}
