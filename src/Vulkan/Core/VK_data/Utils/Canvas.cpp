#include "Canvas.h"

#include <Vulkan/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Canvas::Canvas(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_buffer = new vk::data::Buffer(vk_struct);
  this->vk_vertex = new vk::data::Vertex(vk_struct);
  this->vk_data = new vk::data::Data(vk_struct);

  //---------------------------
}
Canvas::~Canvas(){}

//Main function
void Canvas::init(){
  //---------------------------

  //Generic quad coordinates and UV
  std::vector<glm::vec3> xyz;
  xyz.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
  xyz.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
  xyz.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));

  xyz.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
  xyz.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
  xyz.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));

  std::vector<glm::vec2> uv;
  uv.push_back(glm::vec2(1.0f,  0.0f));
  uv.push_back(glm::vec2(0.0f,  0.0f));
  uv.push_back(glm::vec2(0.0f,  1.0f));

  uv.push_back(glm::vec2(1.0f,  1.0f));
  uv.push_back(glm::vec2(1.0f,  0.0f));
  uv.push_back(glm::vec2(0.0f,  1.0f));

  //Canvas data
  vk::structure::Object& vk_object = *vk_struct->core.data.canvas;
  vk_object.data->name = "vk::canvas";
  vk_object.data->xyz = xyz;
  vk_object.data->uv = uv;
  vk_object.data->size = xyz.size();
  vk_object.data->topology.type = utl::topology::TRIANGLE;

  //Create buffer
  vk_vertex->build_vertex(vk_object);

  //---------------------------
}
void Canvas::clean(){
  //---------------------------

  vk_vertex->clean_vertex(*vk_struct->core.data.canvas);

  //---------------------------
}

}
