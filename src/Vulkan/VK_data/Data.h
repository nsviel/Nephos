#pragma once

#include <Utility/Specific/common.h>

namespace vk::data{class Buffer;}
class VK_texture;
namespace vk::command{class Command;}
namespace vk::binding{class Descriptor;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}
namespace vk::structure{class Pipeline;}


namespace vk::data{

class Data
{
public:
  //Constructor / Destructor
  Data(vk::structure::Vulkan* struct_vulkan);
  ~Data();

public:
  //Main functions
  void insert_data(utl::type::Data* data, utl::type::Pose* pose);
  void update_data(utl::type::Data* data, vk::structure::Object* vk_object);
  void clean();
  void clean_vk_object(vk::structure::Object* vk_object);

  //Pipeline data description
  void pipeline_data_description(vk::structure::Pipeline* pipeline);
  void pipeline_binding_description(vk::structure::Pipeline* pipeline);
  void pipeline_attribut_description(vk::structure::Pipeline* pipeline);
  void pipeline_vertex_input_info(vk::structure::Pipeline* pipeline);

private:
  vk::structure::Vulkan* struct_vulkan;
  Buffer* vk_buffer;
  VK_texture* vk_texture;
  vk::command::Command* vk_command;
  vk::binding::Descriptor* vk_descriptor;
};

}
