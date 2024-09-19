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

  //Function
  std::function<void(Subpass* subpass)> draw_task = [](Subpass* subpass){};
  std::function<void(Subpass* subpass)> update_sampler = [](Subpass* subpass){};

  //Subpass info
  VkSubpassDescription description = {};
  VkSubpassDependency dependency = {};
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;
  int source = -1;
  int index = -1;

  //Pipeline
  std::unordered_map< std::string, std::shared_ptr<vk::structure::Pipeline> > map_pipeline;

  //---------------------------
};

}
