#pragma once

#include <Utility/Specific/common.h>

namespace utl::base{class Shader_info;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Pipeline;}


namespace vk::shader{

class VK_shader
{
public:
  //Constructor / Destructor
  VK_shader(vk::structure::Vulkan* struct_vulkan);
  ~VK_shader();

public:
  //Main function
  void create_pipeline_shader(vk::structure::Pipeline* pipeline);
  void create_pipeline_shader_module(vk::structure::Pipeline* pipeline);
  void create_pipeline_shader_info(vk::structure::Pipeline* pipeline);

  //Subfunction
  VkShaderModule create_shader_module(const std::vector<char>& code);
  std::vector<char> read_file(const std::string& filename);
  void recompile_shader(utl::base::Shader_info* shader_info);
  void run_recompilation(string path_glsl, string path_spir);

private:
  vk::structure::Vulkan* struct_vulkan;

  string path_output;
};

}
