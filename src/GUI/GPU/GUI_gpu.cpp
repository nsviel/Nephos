#include "GUI_gpu.h"

#include <Engine.h>
#include <Vulkan/VK_struct.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/Drawing/VK_drawing.h>
#include <Vulkan/Drawing/DR_ui.h>
#include <Window/Window.h>


//Constructor / Destructor
GUI_gpu::GUI_gpu(Engine* engine){
  //---------------------------

  VK_engine* vk_engine = engine->get_vk_engine();
  VK_drawing* vk_drawing = vk_engine->get_vk_drawing();
  this->vk_struct = vk_engine->get_vk_struct();
  this->ui_drawing = vk_drawing->get_ui_drawing();

  //---------------------------
}
GUI_gpu::~GUI_gpu(){}

//Main function
void GUI_gpu::init_gui_vulkan(){
  Window* window = vk_struct->window.windowManager;
  VkSurfaceKHR surface = vk_struct->window.surface;
  VkRenderPass renderPass = vk_struct->renderpass_ui.renderpass;
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

  VkResult result = vkCreateDescriptorPool(vk_struct->device.device, &pool_info, nullptr, &imguiPool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create gui");
  }

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForVulkan(window->get_window(), true);
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = vk_struct->instance.instance;
  init_info.PhysicalDevice = vk_struct->device.physical_device;
  init_info.Device = vk_struct->device.device;
  init_info.Queue = vk_struct->device.queue_graphics;
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

  vkDestroyDescriptorPool(vk_struct->device.device, imguiPool, nullptr);

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
