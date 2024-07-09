#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace utl::shader{class Info;}
namespace vk{class Structure;}
namespace vk::structure{class Pipeline;}


namespace vk::shader{

class Shader
{
public:
  //Constructor / Destructor
  Shader(vk::Structure* vk_struct);
  ~Shader();

public:
  //Main function
  VkShaderModule create_shader_module(const std::vector<char>& code);
  std::vector<char> read_file(const std::string& filename);
  void recompile_shader(utl::shader::Info* shader_info);
  void run_recompilation(std::string path_glsl, std::string path_spir);

private:
  vk::Structure* vk_struct;

  std::string path_output;
};

}
