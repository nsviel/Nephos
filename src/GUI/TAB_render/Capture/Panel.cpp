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
    if(ImGui::BeginTabItem(master->name.c_str(), NULL)){
      this->show_info(master);
      ImGui::EndTabItem();
    }

    //Master sensor tabs
    for(int i=0; i< master->list_sensor.size(); i++){
      k4n::dev::Sensor* sensor = *std::next( master->list_sensor.begin(), i);


      static string open_tab = sensor->name;
      ImGuiTabItemFlags flag = 0;
      if(k4n_swarm->is_selected_sensor(sensor) && sensor->name != open_tab){
        flag = ImGuiTabItemFlags_SetSelected;
        open_tab = sensor->name;
      }
      if(ImGui::BeginTabItem(sensor->name.c_str(), NULL, flag)){

        this->show_info(sensor);
        kin_capture->kinect_configuration();
        kin_playback->kinect_playback();

        kin_operation->kinect_operation();
        kin_recorder->kinect_recorder();
        ImGui::EndTabItem();
      }

    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void Panel::show_info(k4n::dev::Device* device){
  k4n::dev::Sensor* sensor = k4n_swarm->get_selected_sensor();
  if(sensor == nullptr) return;
  //---------------------------

    ImGui::Separator();
  ImVec4 color = ImVec4(0.4f,1.0f,0.4f,1.0f);
  if(ImGui::BeginTable("Kinect_info##general", 2)){
    //Type
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Type"); ImGui::TableNextColumn();
    //ImGui::TextColored(color, "%s", device->type.c_str());

    //Duration
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", device->player.duration);

    //Recording time
    if(device->player.record){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Record"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f s", device->recorder.ts_rec);
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Panel::transfo_matrix(k4n::dev::Device* device){
  k4n::dev::Sensor* sensor = k4n_swarm->get_selected_sensor();
  if(sensor == nullptr) return;
  //---------------------------

  //Object model matrix
  if(ImGui::Button("...##folder_path")){
    mat4 mat;
    mat[0][0] = 0.0027506351470947267;
    mat[1][0] = -0.9997537136077881;
    mat[2][0] = -0.022024720907211305;
    mat[3][0] = 0.0;

    mat[0][1] = 0.8231128454208374;
    mat[1][1] = -0.010243773460388184;
    mat[2][1] = 0.5677855610847473;
    mat[2][1] = 0.0;

    mat[0][2] = -0.5678713321685791;
    mat[1][2] = -0.019690632820129396;
    mat[2][2] = 0.822881817817688;
    mat[3][2] = 0.0;

    mat[0][3] = 1033.565185546875;
    mat[1][3] = 902.3516235351563;
    mat[2][3] = -904.981201171875;
    mat[3][3] = 1.0;
    sensor->object->data->model = mat;
  }
  mat4& mat = sensor->object->data->model;
  ImGui::Columns(4, "ModelMat");
  for(int i=0; i<4; i++){
    ImGui::Separator();
    for(int j=0;j<4;j++){
      ImGui::Text("%.3f", mat[i][j]);
      ImGui::NextColumn();
    }
  }
  ImGui::Separator();
  ImGui::Columns(1);

  //---------------------------
}


}
