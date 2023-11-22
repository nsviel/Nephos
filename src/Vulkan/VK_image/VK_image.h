#ifndef VK_IMAGE_H
#define VK_IMAGE_H

#include <UTL_specific/common.h>
#include <VK_struct/Struct_vk_image.h>

class Struct_vulkan;
class VK_memory;


class VK_image
{
public:
  //Constructor / Destructor
  VK_image(Struct_vulkan* struct_vulkan);
  ~VK_image();

public:
  void clean_image(Struct_vk_image* image);

  //Generic image creation
  void create_image_view(Struct_vk_image* image);
  void create_image_sampler(Struct_vk_image* texture);

  //image creation
  void create_image(Struct_vk_image* image);
  void create_image_obj(Struct_vk_image* image);
  void bind_image_to_memory(Struct_vk_image* image);

  //Subfunction
  void compute_mipmap(Struct_vk_image* image);
  void generate_mipmap(Struct_vk_image* image);

private:
  Struct_vulkan* struct_vulkan;
  VK_memory* vk_memory;
};

#endif
