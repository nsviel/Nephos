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
  //Main function
  void update_entity(eng::data::Entity* entity);
  void remove_entity(eng::data::Entity* entity);

  //Transformation
  void make_translation(eng::data::Entity* entity, vec3 translation);
  void make_rotation(eng::data::Entity* entity, vec3 rotation);
  void make_rotation_X_90d(eng::data::Entity* entity, int value);
  void make_center(eng::data::Entity* entity);

private:
  Engine* engine;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::camera::Node* node_camera;
  eng::camera::Control* cam_control;
  eng::ope::Transformation* ope_transform;
  eng::ope::Operation* ope_operation;
  eng::ope::Attribut* ope_attribut;
};

}
