#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace utl::shader{class Info;}
namespace vk{class Structure;}
namespace vk::structure{class Pipeline;}
namespace vk::shader{class Shader;}


namespace vk::renderpass{

class Shader
{
public:
  //Constructor / Destructor
  Shader(vk::Structure* vk_struct);
  ~Shader();

public:
  //Main function
  void create_pipeline_shader(vk::structure::Pipeline* pipeline);

  //Subfunction
  void create_pipeline_shader_module(vk::structure::Pipeline* pipeline);
  void create_pipeline_shader_info(vk::structure::Pipeline* pipeline);

private:
  vk::Structure* vk_struct;
  vk::shader::Shader* vk_shader;

  std::string path_output;
};

}
