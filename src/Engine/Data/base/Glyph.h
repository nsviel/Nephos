#pragma once

#include <Utility/Base/Type/Data.h>
#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace cam{class Node;}
namespace dat{class Node;}


namespace utl::entity{

class Glyph : public utl::type::Entity
{
public:
  //Constructor / Destructor
  Glyph(eng::Node* node_engine);
  ~Glyph();

public:
  //Main function
  virtual void init();
  virtual void create(){}
  virtual void reset(){}
  virtual void construct(){}
  virtual void clear();

  //Subfunction
  virtual void update_data();
  virtual void update_pose();
  virtual void update_pose(utl::type::Entity* entity){}
  virtual void update_glyph(){}
  virtual void update_glyph(utl::type::Entity* entity){}
  virtual void set_visibility(bool value);

  inline vec4* get_color(){return &color;}
  inline bool is_need_update(){return need_update;}
  inline std::string get_name(){return name;}
  inline std::string get_path(){return path;}
  inline int get_type(){return type;}

protected:
  //Dependancy
  vk::Node* node_vulkan;
  cam::Node* node_camera;
  dat::Node* node_data;

  //Child
  string path = "";
  bool need_update = false;
  vec4 color = vec4(1, 1, 1, 1);
  int type = -1;
};

}
