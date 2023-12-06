#ifndef STRUCT_DEV_PANEL_H
#define STRUCT_DEV_PANEL_H

#include <TAB_dev/DEV_editor/DEV_code_editor.h>


struct DEV_panel{
  //---------------------------

  void run_editors(){
    for(int i=0; i<vec_editor.size(); i++){
      DEV_code_editor* editor = vec_editor[i];
      editor->run_panel();
    }
  }

  vector<DEV_code_editor*> vec_editor;
  int ID_editor = 0;
  bool show_database = false;

  //---------------------------
};

#endif
