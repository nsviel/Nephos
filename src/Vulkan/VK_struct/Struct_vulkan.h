#pragma once

#include <Vulkan/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <string>


namespace vk::structure{

struct Vulkan{
  //---------------------------

  //Constructor
  Vulkan(utl::Node* node_utility){
    this->profiler = new vk::structure::Profiler(node_utility);
  }

  //General
  std::string name;
  int UID = 0;

  //Structure
  vk::structure::Profiler* profiler;
  vk::structure::Render render;
  vk::structure::Window window;
  vk::structure::Instance instance;
  vk::structure::Device device;
  vk::structure::Swapchain swapchain;
  vk::structure::Data data;
  vk::structure::Parameter param;
  vk::structure::Pool pools;
  vk::structure::Command command;
  vk::structure::queue::Class queue;

  //---------------------------
};

}
