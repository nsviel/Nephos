#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Enum.h>
#include <Vulkan/Core/VK_renderpass/Renderpass/Subpass.h>
#include <Vulkan/Core/VK_pipeline/Structure/Pipeline.h>
#include <Vulkan/Core/VK_renderpass/Structure/Attachment.h>
#include <vulkan/vulkan.h>
#include <unordered_map>
#include <functional>
#include <memory>
#include <iostream>
#include <vector>
#include <string>


namespace vk::structure{

struct Subpass{
  //---------------------------

  //Subpass info
  VkSubpassDescription description = {};
  VkSubpassDependency dependency = {};
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;
  vk::renderpass::Target target = vk::renderpass::SHADER;
  int source = -1;
  int index = -1;

  //Attachment
  vk::structure::Attachment depth;
  std::vector<vk::structure::Attachment> vec_color;
  std::vector<vk::structure::Attachment> vec_color_resolve;
  std::unordered_map< std::string, std::shared_ptr<vk::structure::Pipeline> > map_pipeline;
  std::function<void(Subpass* subpass)> draw_task;

  //---------------------------
};

}
