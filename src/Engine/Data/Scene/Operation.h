#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <Engine/Camera/Namespace.h>

namespace eng::scene{
class Glyph;


class Operation
{
public:
  //ConsOperationtor / DesOperationtor
  Operation(eng::scene::Node* sce_node);
  ~Operation();

public:
  //Main function
  void loop(eng::data::Entity* entity);
  void make_translation(vec3 translation);
  void make_rotation(vec3 rotation);

private:
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::camera::Node* eng_camera;
  eng::ope::Transformation* ope_transform;
};

}
