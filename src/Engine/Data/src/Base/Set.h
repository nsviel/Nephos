#pragma once

#include <Utility/Base/Type/Element.h>
#include <Utility/Specific/Common.h>
#include <image/IconsFontAwesome6.h>

namespace dat::base{class Entity;}


namespace dat::base{

struct Set : public utl::type::Element{
  //---------------------------

  //Info
  std::string name;
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
  dat::base::Entity* selected_entity = nullptr;
  dat::base::Set* selected_subset = nullptr;
  dat::base::Set* set_parent = nullptr;

  std::list<dat::base::Entity*> list_entity;
  std::list<dat::base::Set*> list_subset;

  //---------------------------
};

}
