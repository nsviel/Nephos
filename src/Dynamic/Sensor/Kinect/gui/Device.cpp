#include "Device.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Device::Device(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->dat_set = node_element->get_dat_set();

  this->item_width = 100;

  //---------------------------
}
Device::~Device(){}

//Main function
void Device::show_parameter(std::shared_ptr<dat::base::Set> set){
  if(!set) return;
  //---------------------------

  this->show_list_device(set);

  //---------------------------
  ImGui::Separator();
}

//Subfunction
void Device::show_list_device(std::shared_ptr<dat::base::Set> set){
  //---------------------------

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  ImGui::BeginTable("database_view", 4, flags);

  if(set->list_entity.size() == 0){
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TableNextColumn();
    ImGui::Text("(No devices)");
  }
  else{
    ImGui::TableSetupColumn("");
    ImGui::TableSetupColumn("ID");
    ImGui::TableSetupColumn("Serial number", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 20);
    ImGui::TableHeadersRow();
    for(auto& entity : set->list_entity){
      if(auto sensor = std::dynamic_pointer_cast<k4n::base::Sensor>(entity)){
        ImGui::PushID(sensor->info.serial_number.c_str());

        //Sensor type
        ImGui::TableNextRow(); ImGui::TableNextColumn();
        ImGui::Text("Azur Kinect");

        //Sensor ID
        ImGui::TableNextColumn();
        ImGui::Text("%d", sensor->device.index);

        //Sensor serial number
        ImGui::TableNextColumn();
        ImGui::Text("%s", sensor->info.serial_number.c_str());

        //Sensor capture or not
        ImGui::TableNextColumn();
        if(sensor->is_thread_running()){
          ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
          ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(180, 100, 100, 255));
          if(ImGui::SmallButton("X##399")){
            sensor->stop();
          }
          ImGui::PopStyleColor(2);
        }else{
          ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 133, 100, 255));
          ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 180, 100, 255));
          if(ImGui::SmallButton(ICON_FA_PLAY "##399")){
            sensor->start();
          }
          ImGui::PopStyleColor(2);
        }

        ImGui::PopID();
      }
    }
  }

  ImGui::EndTable();

  //---------------------------
}

}
