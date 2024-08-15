#pragma once

#include <string>

namespace cam{class Node;}
namespace dat::elm{class Node;}
namespace dat::elm{class UID;}
namespace dat::elm{class Structure;}
namespace dat::base{class Entity;}
namespace dat::base{class Object;}
namespace dat::base{class Glyph;}
namespace vk::data{class Data;}
namespace core{class Node;}
namespace sce{class Operation;}
namespace cam{class Control;}
namespace utl::media{class Image;}
namespace dat::atr{class Location;}


namespace dat::elm{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::elm::Node* node_element);
  ~Entity();

public:
  //Main function
  void init_entity(dat::base::Entity* entity);
  void remove_entity(dat::base::Entity* entity);
  void reset_pose(dat::base::Entity* entity);
  void visibility_entity(dat::base::Entity* entity, bool value);
  void update_data(dat::base::Entity* entity);
  void update_pose(dat::base::Entity* entity);

private:
  cam::Node* node_camera;
  core::Node* node_core;
  vk::data::Data* vk_data;
  dat::elm::Structure* dat_struct;
  dat::elm::UID* dat_uid;
  cam::Control* cam_control;
  dat::atr::Location* ope_location;
};

}
