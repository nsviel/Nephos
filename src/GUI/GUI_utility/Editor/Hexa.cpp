#include "Hexa.h"
#include <GUI.h>


namespace gui::editor{

//Constructor / Destructor
Hexa::Hexa(GUI* gui){
  //---------------------------


  //---------------------------
}
Hexa::~Hexa(){}

//Main function
void Hexa::design_panel(){
  //---------------------------


  //---------------------------
}

//Subfunction
void Hexa::design_editor_memory(){
  //---------------------------

  static MemoryEditor mem_edit;
  static char data[0x10000];
  size_t data_size = 0x10000;
  mem_edit.DrawWindow("Memory Editor", data, data_size);

  //---------------------------
}

}
