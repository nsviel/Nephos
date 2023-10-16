#ifndef VK_TEXTURE_H
#define VK_TEXTURE_H

#include "../Struct/struct_image.h"
#include "../Struct/struct_data.h"
#include "../Struct/typedef.h"
#include <Specific/common.h>

class VK_engine;
class VK_struct;
class VK_buffer;
class VK_image;


class VK_texture
{
public:
  //Constructor / Destructor
  VK_texture(VK_engine* vk_engine);
  ~VK_texture();

public:
  //Main functions
  Struct_image* load_texture(string path);
  void clean_texture(Struct_data* object);
  void clean_texture(Struct_image* texture);

  //Texture creation
  void create_texture(Struct_image* texture);
  void create_texture_from_file(Struct_image* texture);
  void copy_buffer_to_image(Struct_image* image, VkBuffer buffer);

private:
  VK_engine* vk_engine;
  VK_struct* vk_struct;
  VK_buffer* vk_buffer;
  VK_image* vk_image;
};

#endif
