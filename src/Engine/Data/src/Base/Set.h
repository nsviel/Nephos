#pragma once

#include <Dynamic/Namespace.h>
#include <Utility/Base/Type/Element.h>
#include <Utility/Base/Type/Pose.h>
#include <image/IconsFontAwesome6.h>
#include <string>
#include <list>

namespace dat::base{class Entity;}
namespace dat::base{class Set;}
namespace dyn::player{class Structure;}


namespace dat::base{

struct Set : public utl::type::Element{
  //---------------------------

  Set(){}
  virtual ~Set(){}
  virtual void reset_set(){}

  //Info
  std::string type = "set";
  std::string icon = ICON_FA_FOLDER;

  int nb_entity = 0;
  int nb_subset = 0;

  bool is_visible = true;
  bool is_lockable = false;
  bool is_locked = false;
  bool is_suppressible = false;
  bool is_open = true;

  //Data
  utl::type::Pose pose;
  dat::base::Entity* active_entity = nullptr;
  dat::base::Set* active_subset = nullptr;
  dat::base::Set* set_parent = nullptr;
  dyn::player::Structure* player = nullptr;

  std::list<dat::base::Entity*> list_entity;
  std::list<dat::base::Set*> list_subset;

  //---------------------------
};

}
