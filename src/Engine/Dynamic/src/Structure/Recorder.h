#pragma once

#include <string>


namespace dyn::recorder{

struct Structure{
  //---------------------------

  std::string dir = "../media/record/ply";
  std::string name = "capture";
  std::string path = "";
  std::string format = "";

  bool enable = false;
  double file_size = 0;
  float ts_rec = 0;
  float ts_beg = -1;

  //---------------------------
};

}
