#ifndef LOADER_H
#define LOADER_H

#include <UTL_specific/Struct/struct_data_file.h>
#include <UTL_specific/Struct/struct_object.h>
#include <UTL_specific/File/Directory.h>
#include <UTL_specific/File/Zenity.h>
#include <string>
#include <vector>

class ENG_data;
class ENG_format;
class ENG_scene;


class ENG_loader
{
public:
  //Constructor / Destructor
  ENG_loader(ENG_data* eng_data);
  ~ENG_loader();

public:
  //Main functions
  Object* load_object(std::string path);
  std::vector<Object*> load_objects(std::vector<std::string> path);
  void load_by_zenity();

  //Subfunctions
  void transfert_data(Object* object, Data_file* eng_data);

private:
  ENG_format* eng_format;
  ENG_scene* eng_scene;

  std::string path_current_dir;
  int ID;
};

#endif
