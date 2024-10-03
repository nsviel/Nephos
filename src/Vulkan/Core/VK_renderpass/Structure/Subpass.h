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
  std::function<void(vk::structure::Subpass& subpass)> draw_task = [](vk::structure::Subpass& subpass){};
  std::function<void(vk::structure::Subpass& subpass)> update_sampler = [](vk::structure::Subpass& subpass){};

  //Subpass info
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;
  int source = -1;
  int index = -1;

  //Pipeline
  std::unordered_map< std::string, std::shared_ptr<vk::structure::Pipeline> > map_pipeline;

  //---------------------------
};

}
