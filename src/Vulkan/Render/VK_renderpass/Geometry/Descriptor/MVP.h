#pragma once


namespace vk::pipeline::geometry{

struct MVP{
  //---------------------------

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  //---------------------------
};

}
