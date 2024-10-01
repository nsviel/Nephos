#pragma once

#include <imgui/core/imgui.h>
#include <memory>

namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Image;}


namespace dat::img::gui{

class Overlay
{
public:
  //Constructor / Destructor
  Overlay();
  ~Overlay();

  //Main function
  void compute_hovered_pixel(std::shared_ptr<utl::base::Image> image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(std::shared_ptr<dat::base::Entity> entity, std::shared_ptr<utl::base::Image> image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(std::shared_ptr<dat::base::Entity> entity, std::shared_ptr<utl::base::Image> image);
  void overlay_pixel(std::shared_ptr<utl::base::Image> image, ImVec2 image_size);

private:
  ImVec2 hovered_pixel;
};

}
