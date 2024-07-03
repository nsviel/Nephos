#include "Navigator.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Navigator::Navigator(){
  //---------------------------

  this->nav_struct = new ldr::gui::navigator::Structure();
  this->nav_header = new ldr::gui::navigator::Header(nav_struct);
  this->nav_content = new ldr::gui::navigator::Content(nav_struct);

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

//Subfunction
void Navigator::add_fct_item_operation(std::function<void()> func){
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
