#ifndef VK_SHADER_H
#define VK_SHADER_H

#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;


class VK_shader
{
public:
  //Constructor / Destructor
  VK_shader(VK_engine* vk_engine);
  ~VK_shader();

public:
  //Main function
  void create_pipeline_shader(Struct_pipeline* pipeline);
  void create_pipeline_shader_module(Struct_pipeline* pipeline);
  void create_pipeline_shader_info(Struct_pipeline* pipeline);

  //Subfunction
  VkShaderModule create_shader_module(const std::vector<char>& code);
  std::vector<char> read_file(const std::string& filename);
  void recompile_shader(Shader_info* shader_info);

private:
  Struct_vulkan* struct_vulkan;

  string path_output;
};

#endif
