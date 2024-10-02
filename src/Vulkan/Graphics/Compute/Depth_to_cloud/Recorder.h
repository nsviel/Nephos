#pragma once

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Storage_image;}
namespace vk::pipeline{class Descriptor;}
namespace vk::compute{class Pipeline;}
namespace vk::data{class Retriever;}
namespace vk::texture{class Storage;}
namespace vk::commandbuffer{class Command_buffer;}
namespace vk::commandbuffer{class Allocator;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Object;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Descriptor_set;}


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
  void update_descriptor(vk::structure::Object& vk_object, vk::structure::Descriptor_set& descriptor_set);
  void dispatch_pipeline(vk::structure::Object& vk_object, vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline, vk::structure::Descriptor_set& descriptor_set);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::compute::Pipeline* vk_pipeline;
  vk::data::Retriever* vk_data;
  vk::commandbuffer::Command_buffer* vk_command;
  vk::commandbuffer::Allocator* vk_command_allocator;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::descriptor::Storage_image* vk_storage;
  vk::texture::Storage* vk_tex_storage;
  vk::pipeline::Descriptor* vk_descriptor;
};

}
