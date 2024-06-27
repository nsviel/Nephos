#include "Canvas.h"

#include <Vulkan/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Canvas::Canvas(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_buffer = new vk::data::Buffer(vk_struct);
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
  utl::base::Data* data = new utl::base::Data();
  data->name = "vk::canvas";
  data->xyz = xyz;
  data->uv = uv;
  data->size = xyz.size();
  data->topology.type = utl::topology::TRIANGLE;

  //Create vk object
  vk_struct->data.canvas.data = data;
  vk_buffer->create_buffers(&vk_struct->data.canvas);

  //---------------------------
}
void Canvas::clean(){
  //---------------------------

  vk_buffer->clean_buffers(&vk_struct->data.canvas);

  //---------------------------
}

}
