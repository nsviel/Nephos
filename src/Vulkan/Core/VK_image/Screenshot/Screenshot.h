#pragma once

#include <vulkan/vulkan.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace vk{class Structure;}
namespace vk::image{class Export;}


namespace vk::image{

class Screenshot
{
public:
  //Constructor / Destructor
  Screenshot(vk::Structure* vk_struct);
  ~Screenshot();

public:
  //Main function
  void make_screenshot_color();
  void make_screenshot_depth();

private:
  vk::Structure* vk_struct;
  vk::image::Export* vk_export;
};

}
