#pragma once

#include <Utility/Base/Namespace.h>
#include <Utility/Base/Entity/Struct_entity.h>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <mutex>

class Engine;

namespace entity{
class Glyph;
class Data;


class Object : public entity::Entity
{
public:
  //Constructor / Destructor
  Object();
  Object(Engine* engine);
  ~Object();

  //Main function
  void update_entity();
  void remove_entity();
  void reset_entity();
  void visibility_entity(bool value);

  inline entity::Object* get_object(){return this;}

public:
  Engine* engine;

  utl::base::Data* data;
  std::list<entity::Glyph*> list_glyph;



  //Infos
  std::string path_file = "";
  std::string path_save = "";
  std::string path_text = "";
  std::string file_format = "";
  std::string draw_type_name = "";
  glm::vec4 unicolor;


  //Pose
  glm::vec3 min = glm::vec3(0.0f);
  glm::vec3 max = glm::vec3(0.0f);
  glm::vec3 root = glm::vec3(0.0f);
  glm::vec3 COM = glm::vec3(0.0f);
  glm::mat4 rotat = glm::mat4(1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  glm::mat4 scale = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 mvp = glm::mat4(1.0f);
};

}
