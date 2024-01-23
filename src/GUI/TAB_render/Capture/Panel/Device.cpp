#include "Device.h"

#include <GUI.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>


namespace gui::kinect{

//Constructor / Destructor
Device::Device(GUI* gui, bool* show_window, string name) : gui::base::Panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::capture::Node* node_capture = engine->get_node_capture();
  k4n::Node* node_kinect = node_capture->get_node_kinect();

  this->k4n_swarm = node_kinect->get_k4n_swarm();
  this->gui_capture = new gui::kinect::Capture(node_kinect);
  this->gui_playback = new gui::kinect::Playback(node_kinect);
  this->gui_recorder = new gui::kinect::Recorder(node_kinect);
  this->gui_player = new gui::kinect::Player(engine);
  this->gui_master = new gui::kinect::Master(node_kinect);
  this->gui_sensor = new gui::kinect::Sensor(node_kinect);

  //---------------------------
}
Device::~Device(){}

//Main function
void Device::run_panel(){
  k4n::dev::Sensor* sensor = k4n_swarm->get_selected_sensor();
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
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  //Master player
  gui_player->draw_player(master);

  //Device info & configuration
  if(master != nullptr && ImGui::BeginTabBar("devices_tab##4567")){
    this->show_master_tab(master);

    //Master sensor tabs -> click = sensor selection
    for(int i=0; i< master->list_sensor.size(); i++){
      k4n::dev::Sensor* sensor = *std::next( master->list_sensor.begin(), i);
      this->show_sensor_tab(sensor);
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Tab function
void Device::show_master_tab(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  string name = master->icon + "  " + "Master";
  if(ImGui::BeginTabItem(name.c_str(), NULL)){
    gui_master->show_master_info(master);
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Device::show_sensor_tab(k4n::dev::Sensor* sensor){
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
ImGuiTabItemFlags Device::get_tab_flag(k4n::dev::Sensor* sensor){
  k4n::dev::Master* master = sensor->master;
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
