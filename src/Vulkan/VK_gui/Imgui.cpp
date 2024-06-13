#include "Imgui.h"

#include <Vulkan/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace vk::gui{

//Constructor / Destructor
Imgui::Imgui(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pool = new vk::instance::Pool(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_window = new vk::window::GLFW(vk_struct);
  this->vk_texture = new vk::image::Texture(vk_struct);
  this->vk_font = new vk::gui::Font(vk_struct);

  //---------------------------
}
Imgui::~Imgui(){}

//Main function
void Imgui::init(){
  //---------------------------

  this->create_context();
  vk_font->create_font();
  this->update_render_descriptor();

  //---------------------------
}
void Imgui::draw(vk::structure::Command_buffer* command_buffer){
  if(vk_struct->param.headless) return;
  //---------------------------

  if(vk_struct->window.resizing) return;
  if(vk_window->is_window_resized()) return;

  ImGui::Render();
  ImDrawData* draw = ImGui::GetDrawData();
  if(draw == nullptr) return;

  ImGui_ImplVulkan_RenderDrawData(draw, command_buffer->handle);

  //---------------------------
}
void Imgui::clean(){
  //---------------------------

  this->glfw_clean();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();

  //---------------------------
}
void Imgui::loop(){
  //---------------------------

  this->glfw_new_frame();

  //---------------------------
}

//Context
void Imgui::create_context(){
  //---------------------------

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  if(!vk_struct->param.headless){
    vk::structure::Renderpass* renderpass = vk_struct->render.get_renderpass_byName("gui");
    ImGui_ImplGlfw_InitForVulkan(vk_struct->window.handle, true);
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = vk_struct->instance.handle;
    init_info.PhysicalDevice = vk_struct->device.physical_device.handle;
    init_info.Device = vk_struct->device.handle;
    init_info.Queue = vk_struct->device.queue.graphics.handle;
    init_info.DescriptorPool = vk_struct->pools.descriptor.allocator;
    init_info.PipelineCache = VK_NULL_HANDLE;
    init_info.MinImageCount = 2;
    init_info.ImageCount = 2;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    init_info.Subpass = 0;
    init_info.QueueFamily = vk_struct->device.queue.graphics.family_ID;
    ImGui_ImplVulkan_Init(&init_info, renderpass->handle);
  }

  //---------------------------
}
void Imgui::glfw_clean(){
  if(vk_struct->param.headless) return;
  //---------------------------

  ImGui_ImplVulkan_DestroyFontUploadObjects();
  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();

  //---------------------------
}
void Imgui::glfw_new_frame(){
  if(vk_struct->param.headless) return;
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();

  //---------------------------
}

//Texture
void Imgui::load_texture(utl::media::Image* utl_image){
  //---------------------------

  utl_image->gui_texture_ID = create_imgui_texture(utl_image->texture_ID);

  //---------------------------
}
void Imgui::update_render_descriptor(){
  if(vk_struct->param.headless) return;
  //---------------------------

  vk::structure::Renderpass* renderpass = vk_struct->render.get_renderpass_byName("edl");
  vk::structure::Image* image = &renderpass->framebuffer->color;

  vk_struct->render.descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //---------------------------
}
ImTextureID Imgui::create_imgui_texture(int UID){
  //---------------------------

  vk::structure::Texture* texture = vk_texture->query_texture(UID);
  if(texture == nullptr) return 0;

  //Retrieve descriptor from vulkan texture
  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(texture->vk_image.sampler, texture->vk_image.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  ImTextureID imgui_texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
  return imgui_texture;
}
ImTextureID Imgui::query_engine_texture(){
  if(vk_struct->render.descriptor == VK_NULL_HANDLE) return 0;
  //---------------------------

  ImTextureID texture = reinterpret_cast<ImTextureID>(vk_struct->render.descriptor);

  //---------------------------
  return texture;
}

}
