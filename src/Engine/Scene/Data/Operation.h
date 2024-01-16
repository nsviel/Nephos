#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Scene/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <Engine/Camera/Namespace.h>

class Engine;

namespace eng::scene{
class Glyph;


class Operation
{
public:
  //ConsOperationtor / DesOperationtor
  Operation(eng::scene::Node* node_scene);
  ~Operation();

public:
  void make_rotation_X_90d(entity::Entity* entity, int value);
  void make_center(entity::Entity* entity);

private:
  Engine* engine;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::camera::Control* cam_control;
  eng::ope::Transformation* ope_transform;
  eng::ope::Operation* ope_operation;
  eng::ope::Attribut* ope_attribut;
};

}
