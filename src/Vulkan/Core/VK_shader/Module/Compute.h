#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace vk{class Structure;}
namespace vk::structure{class Pipeline;}
namespace vk::shader{class File;}


namespace vk::shader{

class Compute
{
public:
  //Constructor / Destructor
  Compute(vk::Structure* vk_struct);
  ~Compute();

public:
  //Main function
  void create_module(vk::structure::Pipeline& pipeline);
  void clean_module(vk::structure::Pipeline& pipeline);

  //Subfunction
  void create_shader_module(vk::structure::Pipeline& pipeline);
  void create_shader_info(vk::structure::Pipeline& pipeline);
  VkShaderModule build_module(const std::vector<char>& code);

private:
  vk::Structure* vk_struct;
  vk::shader::File* vk_file;
};

}
