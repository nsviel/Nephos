#pragma once

#include <Utility/Base/Type/Element.h>
#include <Utility/Specific/Common.h>
#include <image/IconsFontAwesome6.h>

namespace utl::type{class Entity;}


namespace utl::type{

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
  utl::type::Entity* selected_entity = nullptr;
  utl::type::Set* selected_subset = nullptr;
  utl::type::Set* set_parent = nullptr;

  std::list<utl::type::Entity*> list_entity;
  std::list<utl::type::Set*> list_subset;

  //---------------------------
};

}
