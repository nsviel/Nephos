#ifndef VK_DRAW_UI_H
#define VK_DRAW_UI_H

#include <VK_struct/struct_frame.h>
#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_command.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_command;
class VK_descriptor;
class VK_submit;
class VK_data;
class VK_uniform;
class VK_canvas;


class DR_ui
{
public:
  //Constructor / Destructor
  DR_ui(VK_engine* vk_engine);
  ~DR_ui();

public:
  //Main functions
  void draw_ui(Struct_renderpass* renderpass);

  inline void set_imgui_drawdata(ImDrawData* value){this->draw_data = value;}

private:
  Timer timer;

  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_data* vk_data;
  VK_uniform* vk_uniform;
  VK_canvas* vk_canvas;

  ImDrawData* draw_data;
};

#endif
