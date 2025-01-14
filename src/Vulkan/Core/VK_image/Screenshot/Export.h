#pragma once

#include <vulkan/vulkan.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace vk{class Structure;}
namespace vk::screenshot{class Format;}


namespace vk::screenshot{

class Export
{
public:
  //Constructor / Destructor
  Export(vk::Structure* vk_struct);
  ~Export();

public:
  //Main function
  void make_screenshot_color();
  void make_screenshot_depth();

private:
  vk::Structure* vk_struct;
  vk::screenshot::Format* vk_format;
};

}
