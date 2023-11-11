#include "VK_imgui.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_binding/VK_pool.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>


//Constructor / Destructor
VK_imgui::VK_imgui(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pool = new VK_pool(struct_vulkan);
  this->vk_command = new VK_command(struct_vulkan);
  this->vk_submit = new VK_submit(struct_vulkan);
  this->vk_engine = new VK_engine(struct_vulkan);

  //---------------------------
}
VK_imgui::~VK_imgui(){}

//Main function
void VK_imgui::init(){
  Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");
  //---------------------------

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForVulkan(struct_vulkan->window.glfw_window, true);
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = struct_vulkan->instance.instance;
  init_info.PhysicalDevice = struct_vulkan->device.struct_device.physical_device;
  init_info.Device = struct_vulkan->device.device;
  init_info.Queue = struct_vulkan->device.queue_graphics;
  init_info.DescriptorPool = struct_vulkan->pool.descriptor;
  init_info.PipelineCache = VK_NULL_HANDLE;
  init_info.MinImageCount = 3;
  init_info.ImageCount = 3;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  ImGui_ImplVulkan_Init(&init_info, renderpass->renderpass);

  //---------------------------
}
void VK_imgui::draw(Struct_subpass* subpass){
  //---------------------------

  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(draw_data, subpass->command_buffer);

  //---------------------------
}
void VK_imgui::load_font(){
  VkResult result;
  //---------------------------

  Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");
  Struct_subpass* subpass = renderpass->vec_subpass[0];

  vk_pool->reset_command_pool();

  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  result = vkBeginCommandBuffer(subpass->command_buffer, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }



  ImGui_ImplVulkan_CreateFontsTexture(subpass->command_buffer);

  vk_command->stop_command_buffer(subpass->command_buffer);
  vk_submit->submit_command_graphics(subpass->command_buffer);
  vk_engine->device_wait_idle();

  ImGui_ImplVulkan_DestroyFontUploadObjects();

  //---------------------------
}
void VK_imgui::clean(){
  //---------------------------

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}
ImTextureID VK_imgui::engine_texture(){
  //---------------------------

  Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("edl");
  Struct_framebuffer* frame_edl = renderpass->framebuffer;
  Struct_image* image = &frame_edl->color;
  VkDescriptorSet descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  ImTextureID texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
  return texture;
}
