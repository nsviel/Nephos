#include "Loader.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <GUI/GUI_main/Interface/Tab.h>
#include <Engine/Data/Namespace.h>
#include <GUI/TAB_render/Tab/Init.h>
#include <imgui/dialog/ImDialog.h>
#include <image/IconsFontAwesome6.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Loader::Loader(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::Node* eng_data = engine->get_eng_data();

  this->eng_loader = eng_data->get_eng_loader();

  //---------------------------
}
Loader::~Loader(){}

//Main function
void Loader::loader_dialog(){
  //---------------------------

  //eng_loader->load_by_zenity();

  //ImDialog
  string title = "Selection";
  string filter = ", .ply, .pcap, .mkv";
  ImDialog::Instance()->OpenDialog("selection_dialog", title.c_str(), filter.c_str(), "..");
  ImDialog::Instance()->SetFileStyle(IGFD_FileStyleByTypeDir, "", ImVec4(0.5f, 0.63f, 0.75f, 0.9f), ICON_FA_FOLDER);
  ImDialog::Instance()->SetFileStyle(IGFD_FileStyleByTypeFile, "", ImVec4(1.0f, 1.0f, 1.0f, 0.9f), ICON_FA_FILE);
  //ImDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".mkv", IM_COL32(45, 133, 133, 255));

  //---------------------------
}
void Loader::loader_panel(){
  //---------------------------

  // display
  if (ImDialog::Instance()->Display("selection_dialog")){
    // action if OK
    if (ImDialog::Instance()->IsOk()){
      std::string filePathName = ImDialog::Instance()->GetFilePathName();
      std::string filePath = ImDialog::Instance()->GetCurrentPath();
      // action
    }

    // close
    ImDialog::Instance()->Close();
  }

  //---------------------------
}

}
