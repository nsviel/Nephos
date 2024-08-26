#pragma once

#include <Data/Base/Element/Entity.h>
#include <Utility/Base/Data/Data.h>
#include <glm/glm.hpp>
#include <string>


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
  virtual void update_glyph(std::shared_ptr<dat::base::Entity> entity){}
  virtual void update_pose(std::shared_ptr<dat::base::Entity> entity){}

  inline glm::vec4* get_color(){return &color;}
  inline std::string get_name(){return name;}
  inline std::string get_path(){return path;}
  inline bool is_need_update(){return need_update;}
  inline int get_type(){return type;}
  inline void set_color(glm::vec4 color){this->color = color;}

  int type = -1;

protected:
  std::string path = "";
  glm::vec4 color = glm::vec4(1, 1, 1, 1);
  bool need_update = false;
};

}
