#pragma once

#include <Application/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Profiler/Namespace.h>
#include <string>


namespace vk::structure{

struct Vulkan{
  //---------------------------

  //Constructor
  Vulkan(app::Node* node_app){
    app::Configuration* app_config = node_app->get_app_config();
    prf::Node* node_profiler = node_app->get_node_profiler();
    this->profiler = new vk::structure::Profiler(node_profiler);
    this->param.headless = app_config->headless;
    this->param.app_running = &app_config->running;
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
  vk::structure::Data data;
  vk::structure::Parameter param;
  vk::structure::Pool pools;
  vk::structure::Command command;
  vk::structure::queue::Class queue;

  //---------------------------
};

}
