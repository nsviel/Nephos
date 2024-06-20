#include "Info.h"

#include <Dynamic/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Info::Info(dyn::Node* node_dynamic){
  //---------------------------



  //---------------------------
}
Info::~Info(){}

//Main function
void Info::design_info(utl::base::Element* element){
  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)) return;
  //---------------------------

  /*
  dat::base::Set* set = dynamic_cast<dat::base::Set*>(element);
  dyn::base::Player* player = &set->player;
  if(player == nullptr) return;

  if(ImGui::CollapsingHeader("Info##dynamic")){

    ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
    ImGui::BeginTable("master##playback_info", 3);
    //Duration
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", player->ts_duration);

    //FPS
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("FPS"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d fps", player->fps_cur);
    ImGui::SetNextItemWidth(50); ImGui::TableNextColumn();
    ImGui::SliderInt("##56765", &player->fps_qry, 1, 120);

    //Path data
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path"); ImGui::TableNextColumn();
    string path = (player->path.data != "") ? player->path.data : "(not defined)";
    ImGui::TextColored(color, "%s", path.c_str());

    //Size
    if(player->size != 0){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Size"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f Mo", player->size);
    }

    ImGui::EndTable();

    //Recording time
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Record"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", master->recorder.ts_rec);

    //Recording file size
    if(master->recorder.mode == dyn::recorder::MKV){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Size"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f Mo", master->recorder.file_size);
    }
  }

  }
*/

  //---------------------------
}

}
