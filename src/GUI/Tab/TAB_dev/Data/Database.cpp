#include "Database.h"

#include <GUI/Node.h>


namespace gui::dev::data{

//Constructor / Destructor
Database::Database(gui::Node* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  this->path_db = "/home/aether/Desktop/todo/power.db3";
  //this->path_db = "../media/database/database.db3";
  this->database = new utl::element::Database(path_db);

  //---------------------------
}
Database::~Database(){}

//Main function
void Database::design_panel(){
  //---------------------------

  this->display_option();
  this->combo_table();
  this->display_table();

  //---------------------------
}

//Subfunction
void Database::display_option(){
  //---------------------------

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_SizingFixedFit;

  if(ImGui::BeginTable("database_option", 2, flags)){
    ImGui::TableSetupColumn("one");
    ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 100.0f);

    //ADD table
    ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(150);
    static char new_table[256];
    ImGui::InputText("##111", new_table, IM_ARRAYSIZE(new_table));
    ImGui::TableNextColumn();
    if(ImGui::Button("ADD table", ImVec2(100, 0.0f))){
      database->create_table(string(new_table));
    }

    ImGui::TableNextRow();

    //ADD data
    ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(150);
    static char new_data[256];
    ImGui::InputText("##112", new_data, IM_ARRAYSIZE(new_data));
    ImGui::TableNextColumn();
    ImGui::Button("ADD data", ImVec2(100, 0.0f));

    ImGui::EndTable();
  }

  //---------------------------
}
void Database::combo_table(){
  //---------------------------

  vector<string> vec_table = database->retrieve_all_table();
  if(vec_table.size() == 0) return;

  //Table list combo
  static int selectedIndex = 0;
  if(ImGui::BeginCombo("table_combo", vec_table[selectedIndex].c_str())){
    for(int i=0; i<vec_table.size(); i++){
      const bool isSelected = (selectedIndex == i);
      if(ImGui::Selectable(vec_table[i].c_str(), isSelected)){
        selectedIndex = i;
      }

      if(isSelected){
        ImGui::SetItemDefaultFocus();
      }
    }
    ImGui::EndCombo();
  }

  //---------------------------
}
void Database::display_table(){
  //---------------------------

  vector<string> vec_table = database->retrieve_all_table();

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  if(ImGui::BeginTable("database_view", 1, flags)){

    for(int i=0; i<vec_table.size(); i++){
      string& table = vec_table[i];

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      ImGui::PushID(table.c_str());
      ImGui::Text("%s", table.c_str());
      ImGui::PopID();
    }

    ImGui::EndTable();
  }

  //---------------------------
}

}
