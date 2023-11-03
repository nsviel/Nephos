#ifndef GPU_TEXTURE_H
#define GPU_TEXTURE_H

#include <ELE_specific/common.h>
#include <VK_image/VK_texture.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class VK_engine;
class Struct_vulkan;


class GPU_texture
{
public:
  //Constructor / Destructor
  GPU_texture(VK_engine* vk_engine);
  ~GPU_texture();

public:
  //Main functions
  Struct_image* load_texture_from_file(string path);
  Struct_image* load_texture_from_frame(AVFrame* frame);

private:
  Struct_vulkan* vk_struct;
  VK_texture* vk_texture;
};

#endif
