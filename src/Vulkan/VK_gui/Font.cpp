#include "Font.h"

#include <Vulkan/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace vk::gui{

//Constructor / Destructor
Font::Font(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  this->vk_allocator = new vk::command::Allocator(vk_struct);

  //---------------------------
}
Font::~Font(){}

//Main function
void Font::select_font(){
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
    ImFont* font = io.Fonts->AddFontFromFileTTF("../media/config/font/DroidSans.ttf", font_size, &config_text);
    io.Fonts->AddFontFromFileTTF("../media/config/font/fontawesome-webfont.ttf", font_size - 0.5f, &config_icon, icons_ranges);
    font_size += 1.0f;

    if(i == 3){
      font_gui = font;
    }
  }

  font_size = 13.0f;
  for(int i=0; i<10; i++){
    ImFont* font = io.Fonts->AddFontFromFileTTF("../media/config/font/DroidSans.ttf", font_size, &config_editor);
    font_size += 1.0f;
  }

  //Buid the font database
  io.Fonts->Build();

  //Setup fonts
  ImGui::GetIO().FontDefault = font_gui;

  //---------------------------
}
void Font::load_font(){
  if(vk_struct->param.headless) return;
  //---------------------------

  vk::pool::Command_buffer* pool = vk_allocator->query_free_pool(&vk_struct->device.queue.graphics);
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
