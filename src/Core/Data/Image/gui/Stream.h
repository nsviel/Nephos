#pragma once

#include <imgui/core/imgui.h>
#include <memory>

namespace dat::img{class Node;}
namespace vk::interface{class Texture;}
namespace vk::interface{class Render;}
namespace utl::base{class Image;}
namespace utl::base{class Data;}


namespace dat::img::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(dat::img::Node* node_image);
  ~Stream();

public:
  //Main function
  void draw_stream(std::shared_ptr<utl::base::Image> utl_image, ImVec2 dimension);
  void draw_stream(utl::base::Data& data, std::shared_ptr<utl::base::Image> image, ImVec2 dimension);

  //Subfunction
  bool check_image(std::shared_ptr<utl::base::Image> utl_image);

private:
  vk::interface::Texture* vk_texture;
  vk::interface::Render* vk_render;

  float current_timestamp = -1;
  int current_UID = -1;
};

}
