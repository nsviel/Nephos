#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::draw{class Renderpass;}
namespace vk::structure{class Render;}


namespace vk::draw{

class Screenshot
{
public:
  //Constructor / Destructor
  Screenshot(vk::Structure* vk_struct);
  ~Screenshot();

public:
  //Main function
  void make_screenshot(std::shared_ptr<vk::structure::Render> render);

  //Subfunction
  void make_viewport(std::shared_ptr<vk::structure::Render> render);
  void make_recording(std::shared_ptr<vk::structure::Render> render);
  void make_export();

private:
  vk::Structure* vk_struct;
  vk::draw::Renderpass* vk_renderpass;
};

}
