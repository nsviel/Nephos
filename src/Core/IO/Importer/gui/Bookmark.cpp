#include "Bookmark.h"

#include <IO/Importer/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::imp::gui{

//Constructor / Destructor
Bookmark::Bookmark(io::imp::gui::Panel* gui_panel){
  //---------------------------

  io::imp::Node* node_importer = gui_panel->get_node_importer();

  this->io_struct = node_importer->get_io_struct();
  this->io_importer = node_importer->get_io_importer();
  this->io_bookmark = node_importer->get_io_bookmark();
  this->utl_navigator = gui_panel->get_utl_navigator();

  //---------------------------
  this->init_navigator();
}
Bookmark::~Bookmark(){}

//Main function
void Bookmark::init_navigator(){
  //---------------------------

  utl_navigator->add_fct_item_icon([this](std::string path){this->bookmark_icon(path);});

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
  std::list<io::imp::bookmark::Item> list_item = io_bookmark->get_list_item();
  //---------------------------

  for(int i=0; i<list_item.size(); i++){
    io::imp::bookmark::Item& item = *next(list_item.begin(), i);

    //File type icon
    ImVec4 color_icon = ImVec4(item.color_icon.r, item.color_icon.g, item.color_icon.b, item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", item.icon.c_str());

    //Bookmark name button
    ImGui::SameLine();
    std::string path_bookmark = item.path.build();
    int trash_space = item.is_supressible ? 30 : 0;
    int size = ImGui::GetContentRegionAvail().x - trash_space;

    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.04, 0.5));
    std::string label = (item.path.name == "") ? item.path.directory : item.path.name;
    if(ImGui::Button(label.c_str(), ImVec2(size, 0))){
      this->bookmark_button(path_bookmark);
    }
    ImGui::PopStyleVar();
    ImGui::SetItemTooltip("%s", path_bookmark.c_str());

    //Bookmark supression
    if(item.is_supressible){
      ImGui::SameLine();
      std::string ID = path_bookmark + "##supressionbookmark";
      ImGui::PushID(ID.c_str());
      if(ImGui::Button(ICON_FA_TRASH "##supressionbookmark")){
        io_bookmark->remove_path(path_bookmark);
        io_bookmark->save_file_bookmark();
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
    io_struct->path.directory = file_path;
    io_struct->open_navigation = true;
  }
  //If selection is a file go load it
  else{
    //File check
    std::string format = utl::path::get_format_from_path(file_path);
    if(!utl::file::is_exist(file_path)) return;
    if(!io_importer->is_format_supported(format)) return;

    //File load
    utl::base::Path path;
    path.insert(file_path);
    io_importer->load_object(path);
  }

  //---------------------------
}
void Bookmark::bookmark_icon(std::string path){
  //---------------------------

  //Button background if already bookmarked
  bool is_bookmarked = io_bookmark->is_path_bookmarked(path);
  int bg_alpha;
  is_bookmarked ? bg_alpha = 255 : bg_alpha = 0;

  //Draw bookmark button
  std::string ID = path + "##bookmarkbutton";
  ImGui::PushID(ID.c_str());
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, bg_alpha));
  ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(46, 133, 45, 0));
  if(ImGui::SmallButton(ICON_FA_BOOKMARK "##addbookmark")){
    if(is_bookmarked){
      io_bookmark->remove_path(path);
    }else{
      io_bookmark->add_abs_path(path);
    }
    io_bookmark->save_file_bookmark();
  }
  ImGui::PopStyleColor(2);
  ImGui::PopID();

  //---------------------------
}


}
