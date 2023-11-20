#include "GUI_kinect.h"

#include <GUI.h>
#include <UTL_capture/UTL_kinect/Kinect.h>
#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device.h>


//Constructor / Destructor
GUI_kinect::GUI_kinect(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui = gui;
  this->kinect = new Kinect();
  this->struct_kinect = kinect->get_struct_kinect();
  this->k4a_device = new K4A_device(struct_kinect);

  this->item_width = 100;

  //---------------------------
}
GUI_kinect::~GUI_kinect(){}

//Main function
void GUI_kinect::design_panel(){
  //---------------------------

  this->kinect_devices();
  this->kinect_configuration();

  //---------------------------
}

//Subfunction
void GUI_kinect::kinect_devices(){
  //---------------------------

  vector<Struct_k4a_device>& vec_device = struct_kinect->vec_device;

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  static int selected_device = -1;
  if(ImGui::BeginTable("database_view", 2, flags)){
    if(vec_device.size() == 0){
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::TableNextColumn();
      ImGui::Text("(No available devices)");
    }
    else{
      ImGui::TableSetupColumn("Index");
      ImGui::TableSetupColumn("Serial number");
      ImGui::TableHeadersRow();
      for(int i=0; i<vec_device.size(); i++){
        Struct_k4a_device& device = vec_device[i];

        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGui::PushID(device.serial_number.c_str());
        ImGui::Text("%d", device.index);
        ImGui::TableNextColumn();
        if (ImGui::Selectable(device.serial_number.c_str(), selected_device == i, ImGuiSelectableFlags_SpanAllColumns)){
          selected_device = i;
        }
        ImGui::PopID();
      }
    }

    ImGui::EndTable();
  }

  if(ImGui::Button("Refresh", ImVec2(item_width, 0))){
    k4a_device->refresh_device_list();
  }

  //---------------------------
}
void GUI_kinect::kinect_configuration(){
  //---------------------------


  //---------------------------
}
