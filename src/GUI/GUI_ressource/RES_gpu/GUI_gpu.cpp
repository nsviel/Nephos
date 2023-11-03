#include "GUI_gpu.h"

#include <GUI.h>
#include <Engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_engine.h>
#include <VK_drawing/VK_drawing.h>
#include <VK_drawing/DR_ui.h>
#include <ELE_window/Window.h>


//Constructor / Destructor
GUI_gpu::GUI_gpu(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  VK_engine* vk_engine = engine->get_vk_engine();
  VK_drawing* vk_drawing = vk_engine->get_vk_drawing();
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->ui_drawing = vk_drawing->get_ui_drawing();

  //---------------------------
}
GUI_gpu::~GUI_gpu(){}

//Main function
void GUI_gpu::init_gui_vulkan(){
  Window* window = struct_vulkan->window.windowManager;
  VkSurfaceKHR surface = struct_vulkan->window.surface;
  VkRenderPass renderPass = struct_vulkan->renderpass_ui.renderpass;
  //---------------------------

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  // Create Descriptor Pool
  VkDescriptorPoolSize pool_sizes[] ={
    { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
    { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
    { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
    { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
    { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
  };
  VkDescriptorPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
  pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
  pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
  pool_info.pPoolSizes = pool_sizes;

  VkResult result = vkCreateDescriptorPool(struct_vulkan->device.device, &pool_info, nullptr, &imguiPool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create gui");
  }

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForVulkan(window->get_window(), true);
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = struct_vulkan->instance.instance;
  init_info.PhysicalDevice = struct_vulkan->device.physical_device;
  init_info.Device = struct_vulkan->device.device;
  init_info.Queue = struct_vulkan->device.queue_graphics;
  init_info.DescriptorPool = imguiPool;
  init_info.PipelineCache = VK_NULL_HANDLE;
  init_info.MinImageCount = 3;
  init_info.ImageCount = 3;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  ImGui_ImplVulkan_Init(&init_info, renderPass);

  //---------------------------
}
void GUI_gpu::clean_gui_vulkan(){
  //---------------------------

  vkDestroyDescriptorPool(struct_vulkan->device.device, imguiPool, nullptr);

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}

//Render function
void GUI_gpu::render_frame(){
  //---------------------------

  ImGui::Render();
  this->draw_data = ImGui::GetDrawData();
  ui_drawing->set_imgui_drawdata(draw_data);

  //---------------------------
}
void GUI_gpu::render_command(VkCommandBuffer command_buffer){
  //Unused right now
  //---------------------------

  ImGui_ImplVulkan_RenderDrawData(draw_data, command_buffer);

  //---------------------------
}
