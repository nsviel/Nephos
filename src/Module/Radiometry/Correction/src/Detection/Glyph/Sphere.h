#pragma once

#include <Data/Base/Entity/Glyph.h>
#include <memory>

namespace core{class Node;}
namespace cam{class Control;}
//namespace io::imp{class Importer;}


namespace rad::cor::glyph{

class Sphere : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Sphere(core::Node* node_core);
  ~Sphere();

public:
  //Main function
  void create();
  void update_pose(const std::shared_ptr<dat::base::Entity> entity);
  void reset_glyph();

  //Subfunction
  void construct(glm::vec4 color);
  void move_sphere(glm::vec3 pose, float diameter);

private:
  //io::imp::Importer* io_importer;
  cam::Control* cam_control;

  int size = 20;
  glm::mat4 mat_model = glm::mat4(1);
};

}
