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
  this->vk_render = new vk::gui::Render(vk_struct);
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
  vk_render->update_render_texture();

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

//Subfunction
void Imgui::create_context(){
  //---------------------------

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGui::StyleColorsDark();

  //If headless no need to init more
  if(vk_struct->interface.param.headless) return;

  //Init imgui vulkan implementation
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = vk_struct->core.instance.handle;
  init_info.PhysicalDevice = vk_struct->core.device.physical_device.handle;
  init_info.Device = vk_struct->core.device.handle;
  init_info.Queue = vk_struct->core.device.queue.graphics.handle;
  init_info.DescriptorPool = vk_struct->core.pools.descriptor.pool;
  init_info.PipelineCache = VK_NULL_HANDLE;
  init_info.MinImageCount = 2;
  init_info.ImageCount = 2;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  init_info.Subpass = 0;
  init_info.QueueFamily = vk_struct->core.device.queue.graphics.family_ID;
  ImGui_ImplVulkan_Init(&init_info, vk_struct->graphics.render.renderpass.presentation->handle);
  ImGui_ImplGlfw_InitForVulkan(vk_struct->window.handle, true);

  //---------------------------
}
void Imgui::draw_frame(vk::structure::Command_buffer& command_buffer){
  if(vk_struct->interface.param.headless) return;
  //---------------------------

  //Check resizing
  if(vk_struct->window.resizing) return;
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

  vk_render->update_render_texture();

  ImGui::NewFrame();
  vk_docking->loop();

  //---------------------------
}
void Imgui::glfw_clean(){
  if(vk_struct->interface.param.headless) return;
  //---------------------------

  ImGui_ImplVulkan_DestroyFontUploadObjects();
  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();

  //---------------------------
}
void Imgui::glfw_new_frame(){
  if(vk_struct->interface.param.headless) return;
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();

  //---------------------------
}

}
