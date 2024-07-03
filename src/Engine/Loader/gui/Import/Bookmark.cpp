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

  //---------------------------
}
Bookmark::~Bookmark(){}

//Main function
void Bookmark::draw_tab(int width){
  //---------------------------

  ImGui::SetNextItemWidth(width);
  if(ImGui::BeginTabItem("Navigator##50", NULL)){
    this->draw_content();
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Bookmark::draw_content(){
  std::list<ldr::bookmark::Item> list_item = ldr_bookmark->get_list_item();
  //---------------------------

  for(int i=0; i<list_item.size(); i++){
    ldr::bookmark::Item& item = *next(list_item.begin(), i);
    ldr::gui::navigator::File file;
    file.item = item;

    //File type icon
    ImVec4 color_icon = ImVec4(file.item.color_icon.r, file.item.color_icon.g, file.item.color_icon.b, file.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", file.item.icon.c_str());

    //Bookmark name button
    ImGui::SameLine();
    int trash_space = 0;
    file.item.is_supressible ? trash_space = 30 : 0;
    int size = ImGui::GetContentRegionAvail().x - trash_space;
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.04, 0.5));
    if(ImGui::Button(file.item.name.c_str(), ImVec2(size, 0))){
      this->item_bookmark(file.item.path);
    }
    ImGui::PopStyleVar();
    ImGui::SetItemTooltip("%s", file.item.path.c_str());

    //Bookmark supression
    if(file.item.is_supressible){
      ImGui::SameLine();
      std::string ID = file.item.path + "##supressionbookmark";
      ImGui::PushID(ID.c_str());
      if(ImGui::Button(ICON_FA_TRASH "##supressionbookmark")){
        ldr_bookmark->remove_path(file.item.path);
        ldr_bookmark->save_on_file();
      }
      ImGui::PopID();
    }
  }

  //---------------------------
}

  //Subfunction
void Bookmark::item_bookmark(std::string file_path){
  //---------------------------

  //If selection is a directory go display his content
  if(utl::directory::is_directory(file_path)){
    ldr_struct->importer.path.directory = file_path;
  //  this->goto_file_tab = true;
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
void Bookmark::item_bookmark_icon(){
//  if(nav_struct->with_bookmark == false) return;
  //---------------------------
/*
  //Button background if already bookmarked
  bool is_bookmarked = ldr_bookmark->is_path_bookmarked(file.item.path);
  int bg_alpha;
  is_bookmarked ? bg_alpha = 255 : bg_alpha = 0;

  //Draw bookmark button
  std::string ID = file.item.path + "##bookmarkbutton";
  ImGui::TableNextColumn();
  ImGui::PushID(ID.c_str());
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, bg_alpha));
  ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(46, 133, 45, 0));
  if(ImGui::Button(ICON_FA_BOOKMARK "##addbookmark")){
    if(is_bookmarked){
      ldr_bookmark->remove_path(file.item.path);
    }else{
      ldr_bookmark->add_abs_path(file.item.path);
    }
    ldr_bookmark->save_on_file();
  }
  ImGui::PopStyleColor(2);
  ImGui::PopID();
*/
  //---------------------------
}

}
