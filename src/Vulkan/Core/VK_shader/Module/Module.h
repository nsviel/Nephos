#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace vk{class Structure;}
namespace vk::shader{class File;}
namespace vk::shader{class Render;}
namespace vk::shader{class Compute;}
namespace vk::structure{class Pipeline;}


namespace vk::shader{

class Module
{
public:
  //Constructor / Destructor
  Module(vk::Structure* vk_struct);
  ~Module();

public:
  //Main function
  void create_pipeline_module(vk::structure::Pipeline& pipeline);
  void clean_pipeline_module(vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
  vk::shader::File* vk_file;
  vk::shader::Render* vk_render;
  vk::shader::Compute* vk_compute;
};

}
