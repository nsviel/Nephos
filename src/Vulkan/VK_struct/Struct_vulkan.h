#pragma once

#include <Vulkan/VK_window/Structure/Window.h>
#include <Vulkan/VK_data/Structure/Data.h>
#include <Vulkan/VK_queue/Structure/Class.h>
#include <Vulkan/VK_device/Structure/Device.h>
#include <Vulkan/VK_instance/Structure/Instance.h>
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

  //General
  std::string name = "";
  int UID = 0;

  //Structure
  vk::structure::Profiler* profiler;
  vk::structure::Render render;
  vk::structure::Window window;
  vk::structure::Panel panel;
  vk::structure::Instance instance;
  vk::structure::Device device;
  vk::structure::Swapchain swapchain;
  vk::data::structure::Data data;
  vk::structure::Parameter param;
  vk::structure::Pool pools;
  vk::structure::Command command;
  vk::queue::structure::Class queue;

  //---------------------------
};

}
