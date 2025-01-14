#pragma once

#include <vulkan/vulkan.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace vk{class Structure;}
namespace vk::structure{class Image;}


namespace vk::screenshot{

enum Formats{
  BMP = 0,
  JPEG = 1,
  BIN = 2,
};

class Format
{
public:
  //Constructor / Destructor
  Format(vk::Structure* vk_struct);
  ~Format();

public:
  //Main function
  void export_to_format(vk::structure::Image& image, void* data);

  //Subfunction
  void export_to_jpeg(vk::structure::Image& image, void* data);
  void export_to_bmp(vk::structure::Image& image, void* data);
  void export_to_bin(vk::structure::Image& image, void* data);

private:
  vk::Structure* vk_struct;
};

}
