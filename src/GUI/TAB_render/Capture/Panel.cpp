#include "Panel.h"

#include <GUI.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>


namespace gui::kinect{

//Constructor / Destructor
Panel::Panel(GUI* gui, bool* show_window, string name) : gui::base::Panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::capture::Node* node_capture = engine->get_node_capture();
  k4n::Node* node_kinect = node_capture->get_node_kinect();

  this->k4n_swarm = node_kinect->get_k4n_swarm();
  this->kin_capture = new gui::kinect::Capture(node_kinect);
  this->kin_playback = new gui::kinect::Playback(node_kinect);
  this->kin_recorder = new gui::kinect::Recorder(node_kinect);
  this->kin_player = new gui::kinect::Player(engine);
  this->kin_operation = new gui::kinect::Operation(node_kinect);

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
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
void Panel::design_panel(){
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  //Master player
  kin_player->draw_player(master);

  //Device info & configuration
  if(master != nullptr && ImGui::BeginTabBar("devices_tab##4567")){

    //Master tab
    string name = master->icon + "  " + "Master";
    if(ImGui::BeginTabItem(name.c_str(), NULL)){
      this->show_info_master(master);
      ImGui::EndTabItem();
    }

    //Master sensor tabs -> click = sensor selection
    for(int i=0; i< master->list_sensor.size(); i++){
      k4n::dev::Sensor* sensor = *std::next( master->list_sensor.begin(), i);

      //Force tab open if another sensor selected
      ImGuiTabItemFlags flag = 0;
      static int UID = master->selected_entity->UID;
      if(master->is_selected_entity(sensor) && sensor->UID != UID){
        flag = ImGuiTabItemFlags_SetSelected;
        UID = master->selected_entity->UID;
      }
      string name = sensor->icon + "  " + sensor->name;
      if(ImGui::BeginTabItem(name.c_str(), NULL, flag)){

        this->show_info_sensor(sensor);
        kin_capture->kinect_configuration();
        kin_playback->kinect_playback();

        kin_operation->kinect_operation();
        kin_recorder->kinect_recorder();

        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }

  //Tab content
  for(int i=0; i< master->list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *std::next( master->list_sensor.begin(), i);

    if(master->is_selected_entity(sensor)){

    }
  }

  //---------------------------
}

//Subfunction
void Panel::show_info_master(k4n::dev::Master* master){
  k4n::dev::Sensor* sensor = k4n_swarm->get_selected_sensor();
  if(sensor == nullptr) return;
  //---------------------------

    ImGui::Separator();
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  if(ImGui::BeginTable("Kinect_info##general", 2)){
    //Type
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Type"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", master->type.c_str());

    //Duration
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", master->player.duration);

    //Recording time
    if(master->player.record){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Record"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f s", master->recorder.ts_rec);
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Panel::show_info_sensor(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

    ImGui::Separator();
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  if(ImGui::BeginTable("Kinect_info##general", 2)){
    //Type
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Type"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->type.c_str());

    //Transformation matrix file path
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Matrix"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->param.path_transfo.c_str());

    ImGui::EndTable();
  }

  //Object model matrix
  mat4& model = sensor->object->pose->model;
  ImGui::Columns(4, "ModelMat");
  for(int i=0; i<4; i++){
    ImGui::Separator();
    for(int j=0;j<4;j++){
      ImGui::Text("%.3f", model[i][j]);
      ImGui::NextColumn();
    }
  }
  ImGui::Separator();
  ImGui::Columns(1);

  ImVec2 width = ImGui::GetContentRegionAvail();
  if(ImGui::Button("Save##transfomatrix", ImVec2(width.x, 0))){

  }

  //---------------------------
}


}
