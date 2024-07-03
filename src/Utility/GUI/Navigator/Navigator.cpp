#include "Navigator.h"

#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace utl::gui{

//Constructor / Destructor
Navigator::Navigator(){
  //---------------------------

  this->nav_struct = new utl::gui::navigator::Structure();
  this->nav_selection = new utl::gui::navigator::Selection(this);
  this->nav_header = new utl::gui::navigator::Header(this);
  this->nav_content = new utl::gui::navigator::Content(this);

  nav_struct->default_path = utl::path::get_current_directory_path();

  //---------------------------
}
Navigator::~Navigator(){}

//Main function
void Navigator::draw_navigator(utl::base::Path& path){
  //---------------------------

  nav_header->draw_header(path);
  nav_content->draw_content(path);

  //---------------------------
}
void Navigator::make_selection_operation(){
  //---------------------------

  nav_selection->item_operation();

  //---------------------------
}

//Subfunction
void Navigator::add_fct_item_operation(std::function<void(utl::base::Path)> func){
  //---------------------------

  nav_struct->fct_item_operation = func;

  //---------------------------
}
void Navigator::add_fct_item_icon(std::function<void()> func){
  //---------------------------

  nav_struct->vec_icon.push_back(func);

  //---------------------------
}

}
