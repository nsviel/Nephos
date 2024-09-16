#pragma once

#include <imgui/core/imgui.h>
#include <memory>

namespace dat::img{class Node;}
namespace vk::image{class Texture;}
namespace vk{class Interface;}
namespace vk::structure{class Texture;}
namespace utl::media{class Image;}


namespace dat::img::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(dat::img::Node* node_image);
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
  vk::Interface* vk_interface;

  float current_timestamp = -1;
  int current_UID = -1;
};

}
