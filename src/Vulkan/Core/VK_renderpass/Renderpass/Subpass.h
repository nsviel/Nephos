#pragma once

namespace vk::renderpass{class Attachment;}
namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}


namespace vk::renderpass{

class Subpass
{
public:
  //Constructor / Destructor
  Subpass(vk::Structure* vk_struct);
  ~Subpass();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);

  //Subfunction
  void create_subpass_shader(vk::structure::Subpass& subpass);
  void create_subpass_transfert(vk::structure::Subpass& subpass);
  void create_subpass_presentation(vk::structure::Subpass& subpass);
  void create_subpass_description(vk::structure::Subpass& subpass);

private:
  vk::Structure* vk_struct;
  vk::renderpass::Attachment* vk_attachment;
};

}
