#pragma once

#include <VK_struct/Struct_vk_pipeline.h>
#include <VK_struct/Struct_vk_entity.h>
#include <VK_main/Struct_vulkan.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_buffer;
class VK_texture;
class VK_command;
class VK_descriptor;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(Struct_vulkan* struct_vulkan);
  ~VK_data();

public:
  //Main functions
  void insert_object(data::Object* object);
  void clean_entity_all();
  void clean_entity(Struct_vk_entity* data);

  //Pipeline data description
  void pipeline_data_description(Struct_vk_pipeline* pipeline);
  void pipeline_binding_description(Struct_vk_pipeline* pipeline);
  void pipeline_attribut_description(Struct_vk_pipeline* pipeline);
  void pipeline_vertex_input_info(Struct_vk_pipeline* pipeline);

private:
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_texture* vk_texture;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
};
