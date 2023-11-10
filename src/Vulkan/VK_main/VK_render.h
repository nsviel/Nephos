#ifndef VK_RENDER_H
#define VK_RENDER_H

#include <ELE_specific/common.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_image/VK_texture.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class VK_engine;
class VK_drawing;
class VK_texture;
class FPS_counter;
class Struct_vulkan;


class VK_render
{
public:
  //Constructor / Destructor
  VK_render(VK_engine* vk_engine);
  ~VK_render();

public:
  //Main functions
  void loop();
  void add_renderpass_description(Struct_renderpass* renderpass);

  //Texture function
  Struct_image* load_texture_from_file(string path);
  Struct_image* load_texture_from_frame(AVFrame* frame);

  inline Struct_data* get_canvas(){return &struct_vulkan->canvas;}

private:
  FPS_counter* fps_counter;
  Struct_vulkan* struct_vulkan;
  VK_drawing* vk_drawing;
  VK_texture* vk_texture;
};

#endif
