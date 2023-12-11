#pragma once

#include <UTL_specific/common.h>
#include <VK_struct/Namespace.h>

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
  void create_image(vk::structure::Struct_vk_image* image);
  void clean_image(vk::structure::Struct_vk_image* image);

  //Image vulkan creation
  void create_image_obj(vk::structure::Struct_vk_image* image);
  void create_image_view(vk::structure::Struct_vk_image* image);
  void create_image_sampler(vk::structure::Struct_vk_image* texture);

  //Subfunction
  void compute_mipmap(vk::structure::Struct_vk_image* image);
  void generate_mipmap(vk::structure::Struct_vk_image* image);

private:
  Struct_vulkan* struct_vulkan;
  VK_memory* vk_memory;
};
