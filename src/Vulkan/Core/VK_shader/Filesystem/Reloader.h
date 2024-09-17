#pragma once

#include <string>

namespace vk::pipeline{class Pipeline;}
namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}
namespace vk::synchro{class Synchro;}


namespace vk::shader{

class Reloader
{
public:
  //Constructor / Destructor
  Reloader(vk::Structure* vk_struct);
  ~Reloader();

public:
  //Main function
  void hot_shader_reload(std::string shader_1, std::string shader_2);

private:
  vk::Structure* vk_struct;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::synchro::Synchro* vk_synchro;
};

}
