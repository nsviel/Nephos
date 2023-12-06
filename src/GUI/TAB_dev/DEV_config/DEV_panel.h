#pragma once

#include "../DEV_nsp.h"
#include <TAB_dev/DEV_editor/DEV_code_editor.h>


namespace dev{

struct DEV_panel{
  //---------------------------

  void run_editors(){
    for(int i=0; i<vec_editor.size(); i++){
      dev::DEV_code_editor* editor = vec_editor[i];
      editor->run_panel();
    }
  }

  vector<dev::DEV_code_editor*> vec_editor;
  int ID_editor = 0;
  bool show_database = false;

  //---------------------------
};

}


#endif
