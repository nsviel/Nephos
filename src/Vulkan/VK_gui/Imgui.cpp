#include "Imgui.h"

#include <Vulkan/Namespace.h>


namespace vk::gui{

//Constructor / Destructor
Imgui::Imgui(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pool = new vk::instance::Pool(vk_struct);
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  this->vk_allocator = new vk::command::Allocator(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_window = new vk::window::GLFW(vk_struct);
  this->vk_texture = new vk::image::Texture(vk_struct);

  //---------------------------
}
Imgui::~Imgui(){}

//Main function
void Imgui::init(){
  //---------------------------

  this->create_context();
  this->select_font();
  this->load_font();

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

  ImGui_ImplVulkan_RenderDrawData(draw, command_buffer->command);

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

  this->update_render_descriptor();

  //---------------------------
}
void Imgui::new_frame(){
  //---------------------------

  this->glfw_new_frame();
  ImGui::NewFrame();

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
    init_info.DescriptorPool = vk_struct->pools.descriptor.memory;
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

//Font
void Imgui::select_font(){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

  //Configuration - texte
  ImFontConfig config_text;
  config_text.GlyphExtraSpacing.x = 1.0f;

  //Configuration - texte
  ImFontConfig config_editor;
  config_editor.GlyphExtraSpacing.x = 2.0f;
  config_editor.OversampleH = 4.0f;
  config_editor.OversampleV = 4.0f;

  //Configuration - icon
  ImFontConfig config_icon;
  config_icon.MergeMode = true;
  config_icon.GlyphMinAdvanceX = 15.0f; //Monospace icons

  //Load all droidsans font with size from 13 to 23
  float font_size;
  font_size = 10.0f;
  ImFont* font_gui;
  for(int i=0; i<15; i++){
    ImFont* font = io.Fonts->AddFontFromFileTTF("../config/font/DroidSans.ttf", font_size, &config_text);
    io.Fonts->AddFontFromFileTTF("../config/font/fontawesome-webfont.ttf", font_size - 0.5f, &config_icon, icons_ranges);
    font_size += 1.0f;

    if(i == 3){
      font_gui = font;
    }
  }

  font_size = 13.0f;
  for(int i=0; i<10; i++){
    ImFont* font = io.Fonts->AddFontFromFileTTF("../config/font/DroidSans.ttf", font_size, &config_editor);
    font_size += 1.0f;
  }

  //Buid the font database
  io.Fonts->Build();

  //Setup fonts
  ImGui::GetIO().FontDefault = font_gui;

  //---------------------------
}
void Imgui::load_font(){
  if(vk_struct->param.headless) return;
  //---------------------------

  vk::pool::Command_buffer* pool = vk_allocator->query_free_pool(&vk_struct->device.queue.graphics);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  ImGui_ImplVulkan_CreateFontsTexture(command_buffer->command);

  vk_command_buffer->end_command_buffer(command_buffer);
  vk::structure::Command* command = new vk::structure::Command();
  command->command_buffer = command_buffer;
  vk_struct->queue.graphics->add_command(command);

  //---------------------------
}

}
