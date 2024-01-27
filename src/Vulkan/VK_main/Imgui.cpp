#include "Imgui.h"

#include <Vulkan/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Imgui::Imgui(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pool = new vk::instance::Pool(struct_vulkan);
  this->vk_command = new vk::command::Command(struct_vulkan);
  this->vk_submit = new vk::command::Submit(struct_vulkan);
  this->vk_engine = new vk::main::Engine(struct_vulkan);
  this->vk_surface = new vk::presentation::VK_surface(struct_vulkan);

  //---------------------------
}
Imgui::~Imgui(){}

//Main function
void Imgui::init(){
  vk::structure::Renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");
  //---------------------------

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForVulkan(struct_vulkan->window.glfw_window, true);
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = struct_vulkan->instance.instance;
  init_info.PhysicalDevice = struct_vulkan->device.physical_device.physical_device;
  init_info.Device = struct_vulkan->device.device;
  init_info.Queue = struct_vulkan->device.queue_graphics;
  init_info.DescriptorPool = struct_vulkan->pool.descriptor;
  init_info.PipelineCache = VK_NULL_HANDLE;
  init_info.MinImageCount = 2;
  init_info.ImageCount = 2;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  init_info.Subpass = 0;
  init_info.QueueFamily = struct_vulkan->device.physical_device.queue_graphics_idx;
  ImGui_ImplVulkan_Init(&init_info, renderpass->renderpass);

  //---------------------------
}
void Imgui::draw(VkCommandBuffer& command_buffer){
  //---------------------------

  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(draw_data, command_buffer);

  //---------------------------
}
void Imgui::load_font(){
  VkResult result;
  //---------------------------

  vk::structure::Renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");

  vk_pool->reset_command_pool();
  vk_command->start_command_buffer_once(renderpass->command_buffer);

  ImGui_ImplVulkan_CreateFontsTexture(renderpass->command_buffer);

  vk_command->stop_command_buffer(renderpass->command_buffer);
  vk_submit->submit_command_graphics(renderpass->command_buffer);
  vk_engine->device_wait_idle();

  ImGui_ImplVulkan_DestroyFontUploadObjects();

  //---------------------------
}
void Imgui::clean(){
  //---------------------------

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();

  //---------------------------
}

ImTextureID Imgui::rendered_texture(){
  static ImTextureID texture = 0;
  //---------------------------

  bool has_been_resized = check_window_resize();

  if(texture == 0 || struct_vulkan->window.is_resized || has_been_resized){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("edl");
    vk::structure::Image* image = &renderpass->framebuffer->color;

    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    texture = reinterpret_cast<ImTextureID>(descriptor);
  }

  //---------------------------
  return texture;
}
bool Imgui::check_window_resize(){
  //---------------------------

  bool has_been_resized = false;
  static vec2 dim_old = vk_surface->compute_window_dim();
  vec2 dim_new = vk_surface->compute_window_dim();

  if(dim_new.x != dim_old.x || dim_new.y != dim_old.y){
    has_been_resized = true;
    dim_old = dim_new;
  }

  //---------------------------
  return has_been_resized;
}

}
