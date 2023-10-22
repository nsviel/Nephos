#include "GUI_font.h"

#include <Engine.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
GUI_font::GUI_font(Engine* engine){
  //---------------------------

  VK_engine* vk_engine = engine->get_vk_engine();
  this->vk_struct = vk_engine->get_vk_struct();

  //---------------------------
}
GUI_font::~GUI_font(){}

//Main function
void GUI_font::init_gui_font(){
  //---------------------------

  this->gui_select_font();
  this->gui_load_font();

  //---------------------------
}

//Subfunction
void GUI_font::gui_select_font(){
  ImGuiIO io = ImGui::GetIO();
  static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
  //---------------------------

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
  float font_size = 13.0f;
  for(int i=0; i<10; i++){
    io.Fonts->AddFontFromFileTTF("../media/font/DroidSans.ttf", font_size, &config_text);
    io.Fonts->AddFontFromFileTTF("../media/font/fontawesome-webfont.ttf", font_size - 0.5f, &config_icon, icons_ranges);
    font_size += 1.0f;
  }
  this->font_editor = io.Fonts->AddFontFromFileTTF("../media/font/DroidSans.ttf", 15.0f, &config_editor);

  //Buid the font database
  io.Fonts->Build();

  //---------------------------
}
void GUI_font::gui_load_font(){
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
