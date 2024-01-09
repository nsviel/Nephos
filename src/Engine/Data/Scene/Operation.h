#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Data/Namespace.h>
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
  void make_translation(eng::data::Entity* entity, vec3 translation);
  void make_rotation(eng::data::Entity* entity, vec3 rotation);

private:
  Engine* engine;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::camera::Node* node_camera;
  eng::ope::Transformation* ope_transform;
};

}
