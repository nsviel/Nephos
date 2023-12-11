#pragma once

#include <vector>
#include <GUI/TAB_dev/Editor/Namespace.h>
#include <GUI/TAB_dev/Data/Namespace.h>
#include <GUI/TAB_dev/Tab/Namespace.h>


namespace gui::dev::tab{

struct Panel{
  //---------------------------

  void run_editors(){
    for(int i=0; i<vec_editor.size(); i++){
      gui::dev::editor::Editor* editor = vec_editor[i];
      editor->run_panel();
    }
  }

  std::vector<gui::dev::editor::Editor*> vec_editor;
  int ID_editor = 0;
  bool show_database = true;

  //---------------------------
};

}
