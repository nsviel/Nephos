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
  Glyph(){
    //---------------------------

    this->is_selectable = false;

    //---------------------------
  }
  ~Glyph(){}

public:
  virtual void create(){}
  virtual void construct(){}
  virtual void update_glyph(){}
  virtual void update_glyph(dat::base::Entity* entity){}
  virtual void update_pose(dat::base::Entity* entity){}

  inline glm::vec4* get_color(){return &color;}
  inline std::string get_name(){return name;}
  inline std::string get_path(){return path;}
  inline bool is_need_update(){return need_update;}
  inline int get_type(){return type;}

protected:
  std::string path = "";
  glm::vec4 color = glm::vec4(1, 1, 1, 1);
  bool need_update = false;
  int type = -1;
};

}
