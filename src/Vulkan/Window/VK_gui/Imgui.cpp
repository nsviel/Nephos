#include "Imgui.h"

#include <Utility/Namespace.h>
#include <Vulkan/Namespace.h>
#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace vk::gui{

//Constructor / Destructor
Imgui::Imgui(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pool = new vk::instance::Pool(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_texture = new vk::image::Texture(vk_struct);
  this->vk_font = new vk::gui::Font(vk_struct);
  this->vk_docking = new vk::gui::Docking();

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
void Imgui::loop(){
  //---------------------------

  this->glfw_new_frame();

  //---------------------------
}
void Imgui::clean(){
  //---------------------------

  this->glfw_clean();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();

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
  if(!vk_struct->render.param.headless){
    vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.onscreen;
    ImGui_ImplGlfw_InitForVulkan(vk_struct->window.window.handle, true);
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = vk_struct->core.instance.handle;
    init_info.PhysicalDevice = vk_struct->core.device.physical_device.handle;
    init_info.Device = vk_struct->core.device.handle;
    init_info.Queue = vk_struct->core.device.queue.graphics.handle;
    init_info.DescriptorPool = vk_struct->core.pools.descriptor.allocator;
    init_info.PipelineCache = VK_NULL_HANDLE;
    init_info.MinImageCount = 2;
    init_info.ImageCount = 2;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    init_info.Subpass = 0;
    init_info.QueueFamily = vk_struct->core.device.queue.graphics.family_ID;
    ImGui_ImplVulkan_Init(&init_info, renderpass.handle);
  }

  //---------------------------
}
void Imgui::draw_frame(vk::structure::Command_buffer& command_buffer){
  if(vk_struct->render.param.headless) return;
  //---------------------------

  //Check resizing
  if(vk_struct->window.window.resizing) return;
  if(vk_window->is_window_resized()) return;

  //Draw imgui stuff
  ImGui::Render();
  ImDrawData* draw = ImGui::GetDrawData();
  if(draw == nullptr) return;
  ImGui_ImplVulkan_RenderDrawData(draw, command_buffer.handle);

  //---------------------------
}
void Imgui::new_frame(){
  //---------------------------

  ImGui::NewFrame();
  vk_docking->loop();

  //---------------------------
}
void Imgui::resize_event(){
  //---------------------------

  this->update_render_descriptor();

  ImGui::NewFrame();
  vk_docking->loop();

  //---------------------------
}
void Imgui::glfw_clean(){
  if(vk_struct->render.param.headless) return;
  //---------------------------

  ImGui_ImplVulkan_DestroyFontUploadObjects();
  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();

  //---------------------------
}
void Imgui::glfw_new_frame(){
  if(vk_struct->render.param.headless) return;
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();

  //---------------------------
}

//Texture
void Imgui::load_texture(std::shared_ptr<utl::media::Image> utl_image){
  //---------------------------

  utl_image->gui_texture_ID = create_imgui_texture(utl_image->texture_ID);

  //---------------------------
}
void Imgui::update_render_descriptor(){
  if(vk_struct->render.param.headless) return;
  //---------------------------

  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.edl;
  vk::structure::Image* image = &renderpass.framebuffer.color;

  vk_struct->window.gui.descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //---------------------------
}
ImTextureID Imgui::create_imgui_texture(int UID){
  //---------------------------

  std::shared_ptr<vk::structure::Texture> texture = vk_texture->query_texture(UID);
  if(!texture) return 0;

  //Retrieve descriptor from vulkan texture
  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(texture->vk_image.sampler, texture->vk_image.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  ImTextureID imgui_texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
  return imgui_texture;
}
ImTextureID Imgui::query_engine_texture(){
  if(vk_struct->window.gui.descriptor == VK_NULL_HANDLE) return 0;
  //---------------------------

  ImTextureID texture = reinterpret_cast<ImTextureID>(vk_struct->window.gui.descriptor);

  //---------------------------
  return texture;
}

}
