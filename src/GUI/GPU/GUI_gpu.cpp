#include "GUI_gpu.h"

#include <Engine.h>
#include <Vulkan/VK_struct.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/Drawing/VK_drawing.h>
#include <Vulkan/Drawing/DR_ui.h>
#include <image/IconsFontAwesome5.h>
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
void GUI_gpu::clean_gui(){
  //---------------------------

  vkDestroyDescriptorPool(vk_struct->device.device, imguiPool, nullptr);

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}

//Init function
void GUI_gpu::init_gui(){
  //---------------------------

  this->gui_vulkan();
  this->gui_select_font();
  this->gui_load_font();

  //---------------------------
}
void GUI_gpu::gui_vulkan(){
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
void GUI_gpu::gui_select_font(){
  ImGuiIO io = ImGui::GetIO();
  static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
  //---------------------------

  //Configuration - texte
  ImFontConfig config_text;
  config_text.GlyphExtraSpacing.x = 1.0f;

  //Configuration - icon
  ImFontConfig config_icon;
  config_icon.MergeMode = true;
  config_icon.GlyphMinAdvanceX = 15.0f; //Monospace icons

  //Load all droidsans font with size from 13 to 23
  float font_size = 13.0f;
  for(int i=0; i<10; i++){
    io.Fonts->AddFontFromFileTTF("../src/GUI/Style/Font/DroidSans.ttf", font_size, &config_text);
    io.Fonts->AddFontFromFileTTF("../src/GUI/Style/Font/fontawesome-webfont.ttf", font_size - 0.5f, &config_icon, icons_ranges);
    font_size += 1.0f;
  }

  //Buid the font database
  io.Fonts->Build();

  //---------------------------
}
void GUI_gpu::gui_load_font(){
  //---------------------------

  VkResult result = vkResetCommandPool(vk_struct->device.device, vk_struct->command_pool, 0);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  result = vkBeginCommandBuffer(vk_struct->renderpass_ui.command_buffer, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  ImGui_ImplVulkan_CreateFontsTexture(vk_struct->renderpass_ui.command_buffer);

  VkSubmitInfo end_info = {};
  end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  end_info.commandBufferCount = 1;
  end_info.pCommandBuffers = &vk_struct->renderpass_ui.command_buffer;
  result = vkEndCommandBuffer(vk_struct->renderpass_ui.command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  result = vkQueueSubmit(vk_struct->device.queue_graphics, 1, &end_info, VK_NULL_HANDLE);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  result = vkDeviceWaitIdle(vk_struct->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  ImGui_ImplVulkan_DestroyFontUploadObjects();

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
