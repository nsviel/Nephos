#include "Bookmark.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui::importer{

//Constructor / Destructor
Bookmark::Bookmark(ldr::gui::importer::Panel* gui_panel){
  //---------------------------

  ldr::Node* node_loader = gui_panel->get_node_loader();

  this->ldr_struct = node_loader->get_ldr_struct();
  this->ldr_importer = node_loader->get_ldr_importer();
  this->ldr_bookmark = node_loader->get_ldr_bookmark();
  this->gui_navigator = gui_panel->get_gui_navigator();

  //---------------------------
  this->init_navigator();
}
Bookmark::~Bookmark(){}

//Main function
void Bookmark::init_navigator(){
  utl::gui::Navigator* utl_navigator = gui_navigator->get_utl_navigator();
  //---------------------------

  utl_navigator->add_fct_item_icon([this](std::string path) {this->bookmark_icon(path);});

  //---------------------------
}
void Bookmark::draw_tab(int width){
  //---------------------------

  ImGui::SetNextItemWidth(width);
  if(ImGui::BeginTabItem("Bookmark##50", NULL)){
    this->draw_content();
    ImGui::EndTabItem();
  }

  //---------------------------
}

//Subfunction
void Bookmark::draw_content(){
  std::list<ldr::bookmark::Item> list_item = ldr_bookmark->get_list_item();
  //---------------------------

  for(int i=0; i<list_item.size(); i++){
    ldr::bookmark::Item& item = *next(list_item.begin(), i);

    //File type icon
    ImVec4 color_icon = ImVec4(item.color_icon.r, item.color_icon.g, item.color_icon.b, item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", item.icon.c_str());

    //Bookmark name button
    ImGui::SameLine();
    int trash_space = 0;
    item.is_supressible ? trash_space = 30 : 0;
    int size = ImGui::GetContentRegionAvail().x - trash_space;
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.04, 0.5));
    if(ImGui::Button(item.name.c_str(), ImVec2(size, 0))){
      this->bookmark_button(item.path);
    }
    ImGui::PopStyleVar();
    ImGui::SetItemTooltip("%s", item.path.c_str());

    //Bookmark supression
    if(item.is_supressible){
      ImGui::SameLine();
      std::string ID = item.path + "##supressionbookmark";
      ImGui::PushID(ID.c_str());
      if(ImGui::Button(ICON_FA_TRASH "##supressionbookmark")){
        ldr_bookmark->remove_path(item.path);
        ldr_bookmark->save_on_file();
      }
      ImGui::PopID();
    }
  }

  //---------------------------
}
void Bookmark::bookmark_button(std::string file_path){
  //---------------------------

  //If selection is a directory go display his content
  if(utl::directory::is_directory(file_path)){
    ldr_struct->importer.path.directory = file_path;
    bool& open_tab = gui_navigator->get_open_tab();
    open_tab = true;
  }
  //If selection is a file go load it
  else{
    //File check
    std::string format = utl::path::get_format_from_path(file_path);
    if(!utl::file::is_exist(file_path)) return;
    if(!ldr_importer->is_format_supported(format)) return;

    //File load
    utl::base::Path path;
    path.insert(file_path);
    ldr_importer->load_object(path);
  }

  //---------------------------
}
void Bookmark::bookmark_icon(std::string path){
  //---------------------------

  //Button background if already bookmarked
  bool is_bookmarked = ldr_bookmark->is_path_bookmarked(path);
  int bg_alpha;
  is_bookmarked ? bg_alpha = 255 : bg_alpha = 0;

  //Draw bookmark button
  std::string ID = path + "##bookmarkbutton";
  ImGui::PushID(ID.c_str());
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, bg_alpha));
  ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(46, 133, 45, 0));
  if(ImGui::SmallButton(ICON_FA_BOOKMARK "##addbookmark")){
    if(is_bookmarked){
      ldr_bookmark->remove_path(path);
    }else{
      ldr_bookmark->add_abs_path(path);
    }
    ldr_bookmark->save_on_file();
  }
  ImGui::PopStyleColor(2);
  ImGui::PopID();

  //---------------------------
}


}
