#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Operation/Namespace.h>

namespace eng::scene{


class Operation
{
public:
  //ConsOperationtor / DesOperationtor
  Operation(eng::scene::Node* sce_node);
  ~Operation();

public:
  //Main function
  void make_translation();

private:
  eng::scene::Database* sce_database;
  eng::ope::Transformation* ope_transform;
};

}
