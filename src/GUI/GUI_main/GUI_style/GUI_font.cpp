#include "GUI_font.h"

#include <GUI.h>
#include <Engine.h>
#include <VK_engine.h>
#include <VK_struct.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
GUI_font::GUI_font(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
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
  float font_size;
  font_size = 10.0f;
  for(int i=0; i<15; i++){
    ImFont* font = io.Fonts->AddFontFromFileTTF("../media/font/DroidSans.ttf", font_size, &config_text);
    io.Fonts->AddFontFromFileTTF("../media/font/fontawesome-webfont.ttf", font_size - 0.5f, &config_icon, icons_ranges);
    if(i == 0) this->font_gui = font;
    font_size += 1.0f;
    this->vec_font_gui.push_back(font);
  }

  font_size = 13.0f;
  for(int i=0; i<10; i++){
    ImFont* font = io.Fonts->AddFontFromFileTTF("../media/font/DroidSans.ttf", font_size, &config_editor);
    if(i == 0) this->font_editor = font;
    font_size += 1.0f;
    this->vec_font_editor.push_back(font);
  }

  //Buid the font database
  io.Fonts->Build();

  //Setup fonts
  this->font_gui = vec_font_gui[3];
  this->font_small = vec_font_gui[0];
  ImGui::GetIO().FontDefault = font_gui;

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
void GUI_font::combo_font_gui(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if (ImGui::BeginCombo("GUI##Font", font_gui->GetDebugName())){
    for(int i=0; i<vec_font_gui.size(); i++){
      ImFont* font = vec_font_gui[i];
      ImGui::PushID((void*)font);
      if (ImGui::Selectable(font->GetDebugName(), font == font_gui)){
        ImGui::GetIO().FontDefault = font;
        this->font_gui = font;
      }
      ImGui::PopID();
    }
    ImGui::EndCombo();
  }

  //---------------------------
}
void GUI_font::combo_font_editor(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if (ImGui::BeginCombo("Editor##Font", font_editor->GetDebugName())){
    for(int i=0; i<vec_font_editor.size(); i++){
      ImFont* font = vec_font_editor[i];
      ImGui::PushID((void*)font);
      if (ImGui::Selectable(font->GetDebugName(), font == font_editor)){
        this->font_editor = font;
      }
      ImGui::PopID();
    }
    ImGui::EndCombo();
  }

  //---------------------------
}
