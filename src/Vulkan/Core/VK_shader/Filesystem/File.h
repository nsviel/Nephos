#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace vk::shader::structure{class Shader;}
namespace vk{class Structure;}
namespace vk::structure{class Pipeline;}


namespace vk::shader{

class File
{
public:
  //Constructor / Destructor
  File(vk::Structure* vk_struct);
  ~File();

public:
  //Main function
  std::vector<char> read_file(const std::string& filename);
  void recompile_shader(vk::shader::structure::Shader& shader);
  void run_recompilation(std::string path_glsl, std::string path_spir);

private:
  vk::Structure* vk_struct;

  std::string path_output;
};

}
