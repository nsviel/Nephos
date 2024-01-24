#include "Device.h"

#include <Engine/Engine.h>
#include <Utility/Namespace.h>


namespace eng::k4n::gui{

//Constructor / Destructor
Device::Device(eng::k4n::Node* k4n_node, bool* show_window, string name){
  //---------------------------

  this->k4n_swarm = k4n_node->get_k4n_swarm();
  this->gui_capture = new eng::k4n::gui::Capture(k4n_node);
  this->gui_playback = new eng::k4n::gui::Playback(k4n_node);
  this->gui_recorder = new eng::k4n::gui::Recorder(k4n_node);
  this->gui_player = new eng::k4n::gui::Player(k4n_node);
  this->gui_master = new eng::k4n::gui::Master(k4n_node);
  this->gui_sensor = new eng::k4n::gui::Sensor(k4n_node);

  this->show_window = show_window;
  this->name = name;

  //---------------------------
}
Device::~Device(){}

//Main function
void Device::run_panel(){
  eng::k4n::dev::Sensor* sensor = k4n_swarm->get_selected_sensor();
  //---------------------------

  if(*show_window && sensor != nullptr){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Device::design_panel(){
  eng::k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  //Master player
  gui_player->draw_player(master);

  //Device info & configuration
  if(master != nullptr && ImGui::BeginTabBar("devices_tab##4567")){
    this->show_master_tab(master);

    //Master sensor tabs -> click = sensor selection
    for(int i=0; i< master->list_sensor.size(); i++){
      eng::k4n::dev::Sensor* sensor = *std::next( master->list_sensor.begin(), i);
      this->show_sensor_tab(sensor);
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Tab function
void Device::show_master_tab(eng::k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  string name = master->icon + "  " + "Master";
  if(ImGui::BeginTabItem(name.c_str(), NULL)){
    gui_master->show_master_info(master);
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Device::show_sensor_tab(eng::k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  //Force tab open if another sensor selected
  ImGuiTabItemFlags flag = get_tab_flag(sensor);
  string name = sensor->icon + "  " + sensor->name;
  if(ImGui::BeginTabItem(name.c_str(), NULL, flag)){

    gui_sensor->show_sensor(sensor);
    gui_capture->show_sensor_configuration(sensor);
    gui_playback->show_sensor_configuration(sensor);
    //gui_recorder->show_sensor_recorder();

    ImGui::EndTabItem();
  }

  //---------------------------
}

//Subfunction
ImGuiTabItemFlags Device::get_tab_flag(eng::k4n::dev::Sensor* sensor){
  eng::k4n::dev::Master* master = sensor->master;
  //---------------------------

  ImGuiTabItemFlags flag = 0;
  static int UID = master->selected_entity->UID;
  if(master->is_selected_entity(sensor) && sensor->UID != UID){
    flag = ImGuiTabItemFlags_SetSelected;
    UID = master->selected_entity->UID;
  }

  //---------------------------
  return flag;
}

}
