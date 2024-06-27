#include "Font.h"

#include <Vulkan/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace vk::gui{

//Constructor / Destructor
Font::Font(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  this->vk_allocator = new vk::command::Allocator(vk_struct);

  this->path_text = "../media/config/font/DroidSans.ttf";
  this->path_icon = "../extern/fontawesome/webfonts/fa-solid-900.ttf";

  //---------------------------
}
Font::~Font(){}

//Main function
void Font::create_font(){
  //---------------------------

  this->font_text();
  this->font_editor();
  this->font_build();

  //---------------------------
}

//Subfunction
void Font::font_text(){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  //Configuration - texte
  ImFontConfig config_text;
  config_text.GlyphExtraSpacing.x = 1.0f;

  //Configuration - icon
  ImFontConfig config_icon;
  config_icon.MergeMode = true;
  config_icon.GlyphMinAdvanceX = 15.0f; //Monospace icons

  //Load all droidsans font with size from 13 to 23
  static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
  float font_size;
  font_size = 10.0f;
  ImFont* font_gui;
  for(int i=0; i<15; i++){
    ImFont* font = io.Fonts->AddFontFromFileTTF(path_text.c_str(), font_size, &config_text);
    io.Fonts->AddFontFromFileTTF(path_icon.c_str(), font_size - 0.5f, &config_icon, icons_ranges);
    font_size += 1.0f;

    if(i == 3){
      font_gui = font;
    }
  }

  //Setup fonts
  ImGui::GetIO().FontDefault = font_gui;

  //---------------------------
}
void Font::font_editor(){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  //Configuration - texte
  ImFontConfig config_editor;
  config_editor.GlyphExtraSpacing.x = 2.0f;
  config_editor.OversampleH = 4.0f;
  config_editor.OversampleV = 4.0f;

  float font_size = 13.0f;
  for(int i=0; i<10; i++){
    ImFont* font = io.Fonts->AddFontFromFileTTF("../media/config/font/DroidSans.ttf", font_size, &config_editor);
    font_size += 1.0f;
  }

  //---------------------------
}
void Font::font_build(){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  //Buid the font database
  io.Fonts->Build();

  //Insert into engine
  if(vk_struct->param.headless) return;
  vk::pool::structure::Command_buffer* pool = vk_allocator->query_free_pool(&vk_struct->device.queue.graphics);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  ImGui_ImplVulkan_CreateFontsTexture(command_buffer->handle);

  vk_command_buffer->end_command_buffer(command_buffer);
  vk::structure::Command* command = new vk::structure::Command();
  command->command_buffer = command_buffer;
  vk_struct->queue.graphics->add_command(command);

  //---------------------------
}


}
