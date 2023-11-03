#include "EDI_hexa.h"
#include <GUI.h>


//Constructor / Destructor
EDI_hexa::EDI_hexa(GUI* gui){
  //---------------------------


  //---------------------------
}
EDI_hexa::~EDI_hexa(){}

//Main function
void EDI_hexa::design_panel(){
  //---------------------------


  //---------------------------
}

//Subfunction
void EDI_hexa::design_editor_memory(){
  //---------------------------

  static MemoryEditor mem_edit;
  static char data[0x10000];
  size_t data_size = 0x10000;
  mem_edit.DrawWindow("Memory Editor", data, data_size);

  //---------------------------
}
