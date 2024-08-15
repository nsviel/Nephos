#pragma once

#include <imgui/core/imgui.h>

namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::media{class Image;}


namespace dat::ply::gui{

class Overlay
{
public:
  //Constructor / Destructor
  Overlay();
  ~Overlay();

  //Main function
  void compute_hovered_pixel(utl::media::Image* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(dat::base::Entity* entity, utl::media::Image* image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(dat::base::Entity* entity, utl::media::Image* image);
  void overlay_pixel(utl::media::Image* image, ImVec2 image_size);

private:
  ImVec2 hovered_pixel;
};

}
