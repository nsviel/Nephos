#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>


class VK_buffer;
class VK_texture;
class VK_command;
class VK_descriptor;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(vk::structure::Vulkan* struct_vulkan);
  ~VK_data();

public:
  //Main functions
  void insert_object(eng::structure::Object* object);
  void clean_entity_all();
  void clean_entity(vk::structure::Entity* data);

  //Pipeline data description
  void pipeline_data_description(vk::structure::Pipeline* pipeline);
  void pipeline_binding_description(vk::structure::Pipeline* pipeline);
  void pipeline_attribut_description(vk::structure::Pipeline* pipeline);
  void pipeline_vertex_input_info(vk::structure::Pipeline* pipeline);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_texture* vk_texture;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
};
