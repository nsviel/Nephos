#ifndef GPU_TEXTURE_H
#define GPU_TEXTURE_H

#include <Specific/common.h>
#include <Vulkan/Image/VK_texture.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class VK_engine;
class VK_struct;


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
  VK_struct* vk_struct;
  VK_texture* vk_texture;
};

#endif
