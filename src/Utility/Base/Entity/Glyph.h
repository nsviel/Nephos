#pragma once

#include <Utility/Base/Type/Data.h>
#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace eng::cam{class Node;}


namespace utl::entity{

class Glyph : public utl::type::Entity
{
public:
  //Constructor / Destructor
  Glyph(eng::Node* node_engine);
  ~Glyph();

  //Main function
  void clear();
  void update_data();
  void update_pose();
  void set_visibility(bool value);

  virtual void create(){}
  virtual void reset(){}
  virtual void update_pose(utl::type::Entity* entity);
  virtual void update_glyph(){}
  virtual void update_glyph(utl::type::Entity* entity){}

  inline utl::type::Pose* get_pose(){return pose;}
  inline vec4* get_color(){return &color;}
  inline bool is_need_update(){return need_update;}
  inline std::string get_name(){return name;}
  inline int get_type(){return type;}

protected:
  //Dependancy
  vk::Node* node_vulkan;
  eng::cam::Node* node_camera;

  //Child
  utl::type::Pose* pose = nullptr;
  std::string name = "";
  bool need_update = false;
  vec4 color = vec4(1, 1, 1, 1);
  int type = -1;
};

}
