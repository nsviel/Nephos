#ifndef GPU_TEXTURE_H
#define GPU_TEXTURE_H

#include <Specific/common.h>
#include <Vulkan/Image/VK_texture.h>

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
  Struct_image* load_texture(string path);
  void clean_texture(Struct_image* texture);

private:
  VK_struct* vk_struct;
  VK_texture* vk_texture;
};

#endif
