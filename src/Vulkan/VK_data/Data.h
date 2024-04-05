#pragma once

#include <Utility/Specific/Common.h>

namespace vk::data{class Buffer;}
namespace vk::main{class Texture;}
namespace vk::command{class Command_buffer;}
namespace vk::binding{class Descriptor;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}
namespace vk::structure{class Pipeline;}
namespace vk::instance{class UID;}
namespace vk::synchro{class Synchro;}


namespace vk::data{

class Data
{
public:
  //Constructor / Destructor
  Data(vk::structure::Vulkan* vk_struct);
  ~Data();

public:
  //Main functions
  void insert_data(utl::type::Data* data, utl::type::Pose* pose);
  void update_data(utl::type::Data* data, vk::structure::Object* vk_object);
  void clean();
  void clean_vk_object(vk::structure::Object* vk_object);
  void check_data(vk::structure::Object* vk_object);

  //Pipeline data description
  void pipeline_data_description(vk::structure::Pipeline* pipeline);
  void pipeline_binding_description(vk::structure::Pipeline* pipeline);
  void pipeline_attribut_description(vk::structure::Pipeline* pipeline);
  void pipeline_vertex_input_info(vk::structure::Pipeline* pipeline);

private:
  vk::structure::Vulkan* vk_struct;
  Buffer* vk_buffer;
  vk::main::Texture* vk_texture;
  vk::command::Command_buffer* vk_command_buffer;
  vk::binding::Descriptor* vk_descriptor;
  vk::instance::UID* vk_uid;
  vk::synchro::Synchro* vk_synchro;
};

}
