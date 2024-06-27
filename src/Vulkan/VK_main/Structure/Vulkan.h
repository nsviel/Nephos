#pragma once

#include <Vulkan/VK_main/Structure/Profiler.h>
#include <Vulkan/VK_command/Structure/Command.h>
#include <Vulkan/VK_drawing/Structure/Render.h>
#include <Vulkan/VK_window/Structure/Window.h>
#include <Vulkan/VK_data/Structure/Data.h>
#include <Vulkan/VK_queue/Structure/Class.h>
#include <Vulkan/VK_device/Structure/Logical.h>
#include <Vulkan/VK_instance/Structure/Instance.h>
#include <Vulkan/VK_presentation/Structure/Swapchain.h>
#include <Vulkan/VK_pool/Structure/Pool.h>
#include <Application/Node.h>
#include <Vulkan/Namespace.h>
#include <Profiler/Namespace.h>
#include <string>


namespace vk::structure{

struct Vulkan{
  //---------------------------

  //Constructor
  Vulkan(app::Node* node_app){
    prf::Node* node_profiler = node_app->get_node_profiler();
    this->profiler = new vk::structure::Profiler(node_profiler);
    this->window.running = node_app->get_app_running();
  }


  vk::structure::Profiler* profiler;
  vk::structure::Render render;
  vk::structure::Window window;
  vk::structure::Panel panel;
  vk::structure::Instance instance;
  vk::device::structure::Logical device;
  vk::structure::Swapchain swapchain;
  vk::data::structure::Data data;
  vk::structure::Parameter param;
  vk::structure::Pool pools;
  vk::structure::Command command;
  //vk::structure::Profiler profiler;
  vk::queue::structure::Class queue;

  //---------------------------
};

}
