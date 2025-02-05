#pragma once

namespace vk{class Structure;}
namespace vk::image{class Color;}
namespace vk::image{class Depth;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Attachment;}


namespace vk::renderpass{

class Attachment
{
public:
  //Constructor / Destructor
  Attachment(vk::Structure* vk_struct);
  ~Attachment();

public:
  //Main function
  void attachment_shader(vk::structure::Renderpass& renderpass);
  void attachment_transfert(vk::structure::Renderpass& renderpass);
  void attachment_presentation(vk::structure::Renderpass& renderpass);

  //Color attachment
  void color_description(vk::structure::Attachment& color);
  void color_reference(vk::structure::Attachment& color);
  void color_resolve_description(vk::structure::Attachment& color);
  void color_resolve_reference(vk::structure::Attachment& color);

  //Depth attachment
  void depth_description(vk::structure::Attachment& depth);
  void depth_reference(vk::structure::Attachment& depth);

private:
  vk::Structure* vk_struct;
  vk::image::Color* vk_color;
  vk::image::Depth* vk_depth;
};

}
