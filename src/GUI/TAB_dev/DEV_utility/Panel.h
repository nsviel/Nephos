#pragma once

#include "../DEV_nsp.h"
#include <TAB_dev/DEV_editor/Editor.h>


namespace dev{

struct Panel{
  //---------------------------

  void run_editors(){
    for(int i=0; i<vec_editor.size(); i++){
      dev::Editor* editor = vec_editor[i];
      editor->run_panel();
    }
  }

  vector<dev::Editor*> vec_editor;
  int ID_editor = 0;
  bool show_database = false;

  //---------------------------
};

}
