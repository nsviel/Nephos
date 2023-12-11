#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>

class Struct_vulkan;


class VK_shader
{
public:
  //Constructor / Destructor
  VK_shader(Struct_vulkan* struct_vulkan);
  ~VK_shader();

public:
  //Main function
  void create_pipeline_shader(vk::structure::Pipeline* pipeline);
  void create_pipeline_shader_module(vk::structure::Pipeline* pipeline);
  void create_pipeline_shader_info(vk::structure::Pipeline* pipeline);

  //Subfunction
  VkShaderModule create_shader_module(const std::vector<char>& code);
  std::vector<char> read_file(const std::string& filename);
  void recompile_shader(Shader_info* shader_info);
  void run_recompilation(string path_glsl, string path_spir);

private:
  Struct_vulkan* struct_vulkan;

  string path_output;
};
