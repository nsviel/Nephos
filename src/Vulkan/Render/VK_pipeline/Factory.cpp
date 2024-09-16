#include "Factory.h"

#include <Vulkan/Namespace.h>


namespace vk::render::pipeline{

//Constructor / Destructor
Factory::Factory(vk::Structure* vk_struct){
  //---------------------------

  this->pipe_edl = new vk::pipeline::edl::EDL(vk_struct);
  this->pipe_line = new vk::pipeline::topology::Line(vk_struct);
  this->pipe_point = new vk::pipeline::topology::Point(vk_struct);
  this->pipe_triangle = new vk::pipeline::topology::Triangle(vk_struct);

  //---------------------------
}
Factory::~Factory(){}

//Main function
void Factory::add_pipeline_line(vk::structure::Subpass& subpass){
  //---------------------------

  pipe_line->add_pipeline(subpass);

  //---------------------------
}
void Factory::add_pipeline_point(vk::structure::Subpass& subpass){
  //---------------------------

  pipe_point->add_pipeline(subpass);

  //---------------------------
}
void Factory::add_pipeline_triangle(vk::structure::Subpass& subpass){
  //---------------------------

  pipe_triangle->add_pipeline(subpass);

  //---------------------------
}
void Factory::add_pipeline_edl(vk::structure::Subpass& subpass){
  //---------------------------

  pipe_edl->add_pipeline(subpass);

  //---------------------------
}

}
