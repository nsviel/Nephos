#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <Engine/Camera/Namespace.h>

class VK_engine;

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
  void update_entity(eng::data::Entity* entity);
  void remove_entity(eng::data::Entity* entity);
  void make_translation(eng::data::Entity* entity, vec3 translation);
  void make_rotation(eng::data::Entity* entity, vec3 rotation);

private:
  VK_engine* vk_engine;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::camera::Node* eng_camera;
  eng::ope::Transformation* ope_transform;
};

}
