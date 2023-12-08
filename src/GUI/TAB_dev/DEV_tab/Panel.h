#pragma once

#include <vector>
#include <TAB_dev/Panel_nsp.h>
#include <TAB_dev/Tab_nsp.h>


namespace gui::dev::tab{

struct Panel{
  //---------------------------

  void run_editors(){
    for(int i=0; i<vec_editor.size(); i++){
      gui::dev::panel::Editor* editor = vec_editor[i];
      editor->run_panel();
    }
  }

  std::vector<gui::dev::panel::Editor*> vec_editor;
  int ID_editor = 0;
  bool show_database = true;

  //---------------------------
};

}
