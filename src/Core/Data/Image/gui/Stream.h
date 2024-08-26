#pragma once

#include <imgui/core/imgui.h>
#include <memory>

namespace vk{class Node;}
namespace vk::image{class Texture;}
namespace vk::gui{class Imgui;}
namespace vk::structure{class Texture;}
namespace utl::media{class Image;}


namespace dat::img::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(vk::Node* node_vulkan);
  ~Stream();

public:
  //Main function
  void draw_stream(std::shared_ptr<utl::media::Image> utl_image, ImVec2 dimension);

  //Subfunction
  bool check_image(std::shared_ptr<utl::media::Image> utl_image);
  void convert_data_into_texture(std::shared_ptr<utl::media::Image> utl_image);
  void render_image(std::shared_ptr<utl::media::Image> utl_image, ImVec2& dimension);

private:
  vk::image::Texture* vk_texture;
  vk::gui::Imgui* vk_imgui;

  float current_timestamp = -1;
  int current_UID = -1;
};

}
