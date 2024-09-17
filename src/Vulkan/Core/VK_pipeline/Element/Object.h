#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}


namespace vk::pipeline{

class Object
{
public:
  //Constructor / Destructor
  Object(vk::Structure* vk_struct);
  ~Object();

public:
  //Main function
  void create_pipeline_object(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline);

  //Subfunction
  void info_pipeline_topology(vk::structure::Pipeline& pipeline);
  void info_pipeline_dynamic(vk::structure::Pipeline& pipeline);
  void info_pipeline_viewport(vk::structure::Pipeline& pipeline);
  void info_pipeline_rasterization(vk::structure::Pipeline& pipeline);
  void info_pipeline_multisampling(vk::structure::Pipeline& pipeline);
  void info_pipeline_blend_attachment(vk::structure::Pipeline& pipeline);
  void info_pipeline_blend(vk::structure::Pipeline& pipeline);
  void info_pipeline_depth(vk::structure::Pipeline& pipeline);

  //Creation function
  void create_pipeline_handle(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline);
  void clean_pipeline_handle(vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
};

}
