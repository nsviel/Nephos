#pragma once

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
  //Main function
  void create_image(Struct_vk_image* image);
  void clean_image(Struct_vk_image* image);

  //Image vulkan creation
  void create_image_obj(Struct_vk_image* image);
  void create_image_view(Struct_vk_image* image);
  void create_image_sampler(Struct_vk_image* texture);

  //Subfunction
  void compute_mipmap(Struct_vk_image* image);
  void generate_mipmap(Struct_vk_image* image);

private:
  Struct_vulkan* struct_vulkan;
  VK_memory* vk_memory;
};
