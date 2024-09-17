#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace utl::shader{class Info;}
namespace vk{class Structure;}
namespace vk::structure{class Pipeline;}
namespace vk::pipeline::structure{class Shader;}
namespace vk::shader{class File;}


namespace vk::pipeline{

class Shader
{
public:
  //Constructor / Destructor
  Shader(vk::Structure* vk_struct);
  ~Shader();

public:
  //Main function
  void create_pipeline_shader(vk::structure::Pipeline& pipeline);
  void clean_pipeline_shader();

  //Subfunction
  void create_shader_module(vk::structure::Pipeline& pipeline);
  void create_shader_info(vk::structure::Pipeline& pipeline);
  VkShaderModule create_module(const std::vector<char>& code);

private:
  vk::Structure* vk_struct;
  vk::shader::File* vk_file;

  std::vector<vk::pipeline::structure::Shader> vec_shader;
};

}
