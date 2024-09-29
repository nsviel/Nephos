#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::pipeline{class Layout;}
namespace vk::shader{class Module;}
namespace vk::structure{class Pipeline;}


namespace vk::compute{

class Component
{
public:
  //Constructor / Destructor
  Component(vk::Structure* vk_struct);
  ~Component();

public:
  //Main function
  void create_pipeline_component(vk::structure::Pipeline& pipeline);
  void clean_pipeline_component(vk::structure::Pipeline& pipeline);

  //Creation function
  void create_pipeline_handle(vk::structure::Pipeline& pipeline);
  void clean_pipeline_handle(vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
  vk::shader::Module* vk_shader;
  vk::pipeline::Layout* vk_layout;
};

}
