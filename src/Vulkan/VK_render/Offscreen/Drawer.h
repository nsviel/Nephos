#pragma once

namespace vk{class Structure;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::draw{class Drawer;}
namespace vk::structure{class Subpass;}
namespace utl::base{class Data;}


namespace vk::render::offscreen{

class Drawer
{
public:
  //Constructor / Destructor
  Drawer(vk::Structure* vk_struct);
  ~Drawer();

public:
  //Main function
  void draw_scene(vk::structure::Subpass* subpass);

  //Subfunction
  void cmd_draw_point(vk::structure::Subpass* subpass);
  void cmd_draw_line(vk::structure::Subpass* subpass);
  void cmd_draw_triangle(vk::structure::Subpass* subpass);
  bool check_data(utl::base::Data& data, int typology);
  
private:
  vk::Structure* vk_struct;
  vk::binding::Descriptor* vk_descriptor;
  vk::binding::Uniform* vk_uniform;
  vk::draw::Drawer* vk_drawer;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
};

}
