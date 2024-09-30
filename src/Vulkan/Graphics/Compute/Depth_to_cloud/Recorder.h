#pragma once

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Storage;}
namespace vk::compute{class Pipeline;}
namespace vk::data{class Function;}
namespace vk::texture{class Data;}
namespace vk::command{class Command;}
namespace vk::command{class Allocator;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Object;}
namespace vk::structure{class Command_buffer;}


namespace vk::compute::dtc{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(vk::Structure* vk_struct);
  ~Recorder();

public:
  //Main function
  void run_compute(vk::structure::Object& vk_object);

  //Subfunction
  void bind_pipeline(vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline);
  void create_texture(vk::structure::Object& vk_object);
  void update_descriptor(vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline);
  void dispatch_pipeline(vk::structure::Object& vk_object, vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::compute::Pipeline* vk_pipeline;
  vk::data::Function* vk_data;
  vk::command::Command* vk_command;
  vk::command::Allocator* vk_command_allocator;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::descriptor::Storage* vk_storage;
  vk::texture::Data* vk_texture;
};

}
