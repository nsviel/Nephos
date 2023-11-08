#ifndef VK_DATA_H
#define VK_DATA_H

#include <VK_struct/Struct_pipeline.h>
#include <VK_struct/Struct_data.h>
#include <VK_struct/Struct_vulkan.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_buffer;
class VK_texture;
class VK_binding;
class VK_command_buffer;
class VK_descriptor;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(VK_engine* vk_engine);
  ~VK_data();

public:
  //Insertion functions
  void insert_object(Object* object);

  //Clean function
  void clean_data(Struct_data* data);
  void clean_data_all();
  void clean_data_scene(int ID);

  //Pipeline data description
  void create_data_description(Struct_pipeline* pipeline);
  void create_vertex_description(Struct_pipeline* pipeline);
  void create_attribut_description(Struct_pipeline* pipeline);
  void combine_description(Struct_pipeline* pipeline);
  void check_for_attribut(Struct_data* data);

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_texture* vk_texture;
  VK_binding* vk_binding;
  VK_command_buffer* vk_command_buffer;
  VK_descriptor* vk_descriptor;
};

#endif
