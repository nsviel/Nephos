#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::descriptor::structure{class Layout;}
namespace vk::structure{class Image;}
namespace vk::structure{class Pipeline;}
namespace utl::base{class Data;}


namespace vk::descriptor{

class Layout
{
public:
  //Constructor / Destructor
  Layout(vk::Structure* vk_struct);
  ~Layout();

public:
  //Main function
  void create_layout(vk::descriptor::structure::Layout& layout);
  void clean_layout(vk::descriptor::structure::Layout& layout);

  //Subfunction
  void make_required_binding(vk::descriptor::structure::Layout& layout);
  void create_layout_object(vk::descriptor::structure::Layout& layout);

private:
  vk::Structure* vk_struct;
};

}
