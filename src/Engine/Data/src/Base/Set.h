#pragma once

#include <Dynamic/src/Base/Player.h>
#include <Utility/Base/Type/Element.h>
#include <Utility/Base/Type/Pose.h>
#include <image/IconsFontAwesome6.h>
#include <string>
#include <list>

namespace dat::base{class Entity;}
namespace dyn::base{class Player;}


namespace dat::base{

struct Set : public utl::type::Element{
  //---------------------------

  Set();
  ~Set();
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
  dyn::base::Player player;

  std::list<dat::base::Entity*> list_entity;
  std::list<dat::base::Set*> list_subset;

  //---------------------------
};

}
