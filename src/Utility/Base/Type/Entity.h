#pragma once

#include <Utility/Specific/common.h>
#include <image/IconsFontAwesome6.h>


namespace utl::type{
class Set;

struct Entity
{
  //---------------------------

  virtual ~Entity(){}
  virtual void update_data(){}
  virtual void update_pose(){}
  virtual void remove_entity(){}
  virtual void reset_entity(){}
  virtual void set_visibility(bool value){}
  virtual utl::type::Pose* get_pose(){return nullptr;}
  virtual utl::type::Data* get_data(){return nullptr;}
  virtual vector<utl::type::Data*> get_vec_data(){return vector<utl::type::Data*>();}

  inline bool get_visibility(){return is_visible;}

  int UID = -1;
  bool is_suppressible = true;
  bool is_permanent = false;
  bool is_movable = true;
  bool is_visible = true;
  std::string name = "";
  std::string entity_type = "base";
  std::string icon = ICON_FA_FILE;
  utl::type::Set* set_parent = nullptr;

  //---------------------------
};

}
