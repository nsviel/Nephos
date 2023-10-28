#ifndef STRUCT_DEV_PANEL_H
#define STRUCT_DEV_PANEL_H

#include <Dev/Editor/GUI_code_editor.h>


struct GUI_dev_panel{
  //---------------------------

  void run_editors(){
    for(int i=0; i<vec_editor.size(); i++){
      GUI_code_editor* editor = vec_editor[i];
      editor->run_panel();
    }
  }

  vector<GUI_code_editor*> vec_editor;
  int ID_editor = 0;

  //---------------------------
};

#endif
