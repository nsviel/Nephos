#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace vk{class Structure;}
namespace vk::structure{class Pipeline;}
namespace vk::shader{class File;}


namespace vk::pipeline{

class Render
{
public:
  //Constructor / Destructor
  Render(vk::Structure* vk_struct);
  ~Render();

public:
  //Main function
  void create_render_module(vk::structure::Pipeline& pipeline);

  //Subfunction
  void create_shader_module(vk::structure::Pipeline& pipeline);
  void create_shader_info(vk::structure::Pipeline& pipeline);
  VkShaderModule create_module(const std::vector<char>& code);

private:
  vk::Structure* vk_struct;
  vk::shader::File* vk_file;
};

}
