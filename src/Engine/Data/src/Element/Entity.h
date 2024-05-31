#pragma once

#include <string>

namespace cam{class Node;}
namespace dat{class Node;}
namespace dat{class Structure;}
namespace dat::base{class Entity;}
namespace dat::base{class Object;}
namespace dat::base{class Glyph;}
namespace vk::main{class Engine;}
namespace eng{class Node;}
namespace sce{class Operation;}
namespace cam{class Control;}
namespace utl::media{class Image;}



namespace dat{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::Node* node_data);
  ~Entity();

public:
  //Main function
  void init_entity(dat::base::Entity* entity);
  void remove_entity(dat::base::Entity* entity);
  void reset_entity(dat::base::Entity* entity);
  void visibility_entity(dat::base::Entity* entity, bool value);
  void update_data(dat::base::Entity* entity);
  void update_pose(dat::base::Entity* entity);

private:
  cam::Node* node_camera;
  eng::Node* node_engine;
  vk::main::Engine* vk_engine;
  dat::Structure* dat_struct;
  cam::Control* cam_control;
};

}
