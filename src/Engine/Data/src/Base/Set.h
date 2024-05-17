#pragma once

#include <Dynamic/src/Player/Player.h>
#include <Utility/Base/Type/Element.h>
#include <Utility/Base/Type/Pose.h>
#include <image/IconsFontAwesome6.h>
#include <string>
#include <list>

namespace dat::base{class Entity;}
namespace dyn{class Player;}


namespace dat::base{

struct Set : public utl::base::Element{
  //---------------------------

  Set(){}
  ~Set(){}
  virtual void reset(){}
  virtual void info(){}

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
  dyn::base::Player* player = nullptr;
  utl::base::Pose pose;
  dat::base::Entity* active_entity = nullptr;
  dat::base::Set* active_subset = nullptr;
  dat::base::Set* set_parent = nullptr;

  std::list<dat::base::Entity*> list_entity;
  std::list<dat::base::Set*> list_subset;

  //---------------------------
};

}
