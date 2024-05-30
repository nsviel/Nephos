#pragma once

#include <Data/src/Base/Entity.h>
#include <Utility/Base/Type/Data.h>
#include <glm/glm.hpp>
#include <string>

namespace vk{class Node;}
namespace eng{class Node;}
namespace cam{class Node;}
namespace dat{class Node;}


namespace dat::base{

class Glyph : public dat::base::Entity
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
  virtual void remove();

  //Subfunction
  virtual void update_data();
  virtual void update_pose();
  virtual void update_pose(dat::base::Entity* entity){}
  virtual void update_glyph(){}
  virtual void update_glyph(dat::base::Entity* entity){}
  virtual void set_visibility(bool value);

  inline glm::vec4* get_color(){return &color;}
  inline std::string get_name(){return name;}
  inline std::string get_path(){return path;}
  inline bool is_need_update(){return need_update;}
  inline int get_type(){return type;}

protected:
  //Dependancy
  vk::Node* node_vulkan;
  cam::Node* node_camera;
  dat::Node* node_data;

  //Child
  std::string path = "";
  glm::vec4 color = glm::vec4(1, 1, 1, 1);
  bool need_update = false;
  int type = -1;
};

}
