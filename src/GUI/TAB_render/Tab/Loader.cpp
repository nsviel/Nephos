#include "Loader.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <GUI/GUI_main/Interface/Tab.h>
#include <Engine/Data/Namespace.h>
#include <GUI/TAB_render/Tab/Init.h>
#include <imgui/dialog/ImDialog.h>


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
  ImDialog::Instance()->OpenDialog("selection_dialog", "Selection", ".ply, .pcap, .mkv", "..");

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
